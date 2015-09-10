#include <src/Utilities/Utilities.hpp>
#include <stdint.h>
#include "service.hpp"

#include <bb/Application>
#include <bb/platform/Notification>
#include <bb/platform/NotificationDefaultApplicationSettings>
#include <bb/system/InvokeManager>
#include <bb/data/JsonDataAccess>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QtNetwork/QtNetwork>

using bb::data::JsonDataAccess;
using namespace bb::platform;
using namespace bb::system;

const QString AUTHOR 		    = "NEMORY";
const QString APPNAME 		    = "MESSENGER";

bool firstInstalled             = true;
bool hub_initialized            = false;

QVariantMap friends_map;

Service::Service(bb::Application * app)	:
		_invokeManager(new InvokeManager()),
		_testAccount(NULL),
		_hubCache(NULL),
		_udsUtil(NULL),
		_settings(NULL),
		_itemCounter(0),
		_app(app)
{
//    bool started = false;
//
//    _settings = new QSettings(AUTHOR, APPNAME);
//    _invokeManager->setParent(this);
//
//    bool connectResult = connect(_invokeManager, SIGNAL(invoked(const bb::system::InvokeRequest&)), this, SLOT(onInvoked(const bb::system::InvokeRequest&)));
//    qDebug() << "#### Service:: invokeManager connectResult: " << connectResult;
//
//    switch(_invokeManager->startupMode())
//    {
//        case ApplicationStartupMode::LaunchApplication:
//            qDebug() << "#### Service:: Regular application launch";
//            break;
//        case ApplicationStartupMode::InvokeApplication:
//            qDebug() << "#### Service:: Launching app from invoke";
//            break;
//        case ApplicationStartupMode::InvokeCard:
//            qDebug() << "#### Service:: Launching card from invoke";
//            break;
//        case 4:
//            qDebug() << "#### Service:: Launching headless from invoke";
//            started = true;
//            break;
//        default:
//            qDebug() << "#### Service::  other launch: " << _invokeManager->startupMode();
//            break;
//    }
//
//    initialize();
}

void Service::refresh_all()
{
    QString access_token = Utilities::get_string_from_file("data/current_access_token.txt");
    QString notifications = Utilities::get_string_from_file("data/notifications.txt");

    if(access_token.length() > 0 && notifications != "false")
    {
        QString fql = "SELECT thread_id,unread,updated_time,snippet,snippet_author FROM thread WHERE viewer_id = me() AND folder_id = 0 AND (unread > 0 OR unseen > 0)";

        request("https://graph.facebook.com/fql?q=" + fql + "&access_token=" + access_token, "unread_threads_fql");
    }
}

void Service::request(QString full_url, QString endpoint)
{
    QNetworkRequest request;
    request.setUrl(QUrl(full_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QNetworkReply* reply = networkAccessManager.get(request);
    reply->setProperty("endpoint", endpoint);
    reply->setProperty("full_url", full_url);
    connect (reply, SIGNAL(finished()), this, SLOT(onComplete()));

    qDebug() << "#### SERVICE:: NEM API: " << full_url << ", endpoint: " << endpoint;
}

bool Service::thread_exists(QString id)
{
    QString hub_items_string   = Utilities::get_string_from_file("data/hub_items.json");

    bool exists = false;

    if(hub_items_string.length() > 0)
    {
        JsonDataAccess jda;
        QVariantList hub_items_list = jda.loadFromBuffer(hub_items_string).toList();

        if(hub_items_list.size() > 0)
        {
            foreach(QVariant item, hub_items_list)
            {
                QVariantMap attributes_map  = item.toMap();
                QString thread_id           = attributes_map["thread_id"].toString();

                if(id == thread_id)
                {
                    exists = true;
                    break;
                }
            }
        }

        hub_items_list.clear();

        jda.deleteLater();
    }

    hub_items_string.clear();

    return exists;
}

void Service::onComplete()
{
    QNetworkReply* reply        = qobject_cast<QNetworkReply*>(sender());
    QString status              = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString();
    QString reason              = reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
    QString full_url            = reply->property("full_url").toString();
    QString endpoint            = reply->property("endpoint").toString();

    QString response;

    if (reply)
    {
        const int available = reply->bytesAvailable();

        if (available > 0)
        {
            const QByteArray buffer(reply->readAll());
            response = QString::fromUtf8(buffer);
        }

        reply->deleteLater();
    }

    if (response.trimmed().isEmpty())
    {
        response = "empty response error";
    }

    if(status == "200")
    {
        response = ((response.length() > 0 && response != "error") ? response : status);

        Utilities::set_string_to_file(response, "data/inbox_" + Utilities::get_string_from_file("data/current_user_id.txt") + ".json");

        if(response.length() > 0 && Utilities::contains(response, "{"))
        {
            JsonDataAccess jda;
            QVariantMap jsonDATA  = jda.loadFromBuffer(response).toMap();
            jda.deleteLater();

            if(endpoint == "unread_threads_fql")
            {
                QVariantList thread_list = jsonDATA["data"].toList();

                if(thread_list.length() > 0)
                {
                    foreach(QVariant thread, thread_list)
                    {
                        QString thread_id       = thread.toMap()["thread_id"].toString();
                        QString snippet         = thread.toMap()["snippet"].toString();
                        QString snippet_author  = thread.toMap()["snippet_author"].toString();

                        QString from = friends_map[snippet_author].toString();

                        if(from.length() == 0)
                        {
                            from = "Messenger";
                        }

                        if(thread_exists(thread_id))
                        {
                            notifyHub(thread_id, thread_id, from, snippet, snippet, "chat", "update", false);
                        }
                        else
                        {
                            notifyHub(thread_id, thread_id, from, snippet, snippet, "chat", "add", false);
                        }
                    }
                }
            }
        }

        response.clear();
    }

    qDebug() << "#### Service:: status: " << status << ", endpoint: " << endpoint << ", response: " << response;

    full_url.clear();
    status.clear();
}

void Service::onInvoked(const bb::system::InvokeRequest& request)
{
    initialize();

    QString action  = request.action();
    QString data    = request.data();

    qDebug() << "#### Service::onInvoked() action: " + action + ", data: " + data;

    if(action == "bb.action.COMMAND")
    {
        if(data.contains("new_announcements", Qt::CaseInsensitive))
        {
            QString can_announce = Utilities::get_string_from_file("data/can_announce.json");

            if(can_announce == "true")
            {
                QString title = "Messenger Announcements";
                QString message = "Some worthwile announcements from Nemory Studios.";

                notifyHub("", "accountID", title, message, message, "announcement", "add", true);

                Utilities::set_string_to_file("false", "data/can_announce.json");
            }
        }
        else if(data == "refresh")
        {
            refresh_all();
        }
        else if(data == "parse_all_friends")
        {
            QString all_friends_keyvalue_pair = Utilities::get_string_from_file("data/all_friends_keyvalue_pair.json");

            if(all_friends_keyvalue_pair.length() > 0)
            {
                JsonDataAccess jda;
                friends_map  = jda.loadFromBuffer(all_friends_keyvalue_pair).toMap();
                jda.deleteLater();

                qDebug() << "### Service:: all_friends_keyvalue_pair: " << all_friends_keyvalue_pair.length();
            }
        }
        else if(data == "update_hub_account")
        {
            QString _displayName                    = "Messenger";
            QString _description                    = "";
            QString _serverName                     = "messenger.com";
            QString _iconFilename                   = "acc_uncolored.png";
            QString _lockedIconFilename             = "acc_locked_uncolored.png";
            QString _composeIconFilename            = "acc_compose_uncolored.png";
            bool _supportsCompose                   = true;
            QString _headlessTarget                 = "lcom.nemory.fbmessenger.headless";

            QString hub_account_name = Utilities::get_string_from_file("data/hub_account_name.json");

            bool result = _udsUtil->updateAccount(_hubCache->accountId(), _displayName, _headlessTarget, _iconFilename, _lockedIconFilename, _composeIconFilename, hub_account_name, _supportsCompose, UDS_ACCOUNT_TYPE_OTHER);

            qDebug() << "_udsUtil->updateAccount RESULT: " << result;
        }
        else if(data == "stop")
        {
            _app->requestExit();
        }
    }
    else if(action == "bb.action.STOP")
    {
        _app->requestExit();
    }
    else
    {
        JsonDataAccess jda;

        QVariantMap objectMap = (jda.loadFromBuffer(request.data())).toMap();

        if(!jda.hasError())
        {
            QVariantMap attributesMap = objectMap["attributes"].toMap();

            qint64 itemId;

            if (attributesMap["sourceId"].toString().length() > 0)
            {
                itemId = attributesMap["sourceId"].toLongLong();
            }
            else if (attributesMap["messageid"].toString().length() > 0)
            {
                itemId = attributesMap["messageid"].toLongLong();
            }

            if(action == "bb.action.VIEW")
            {
                _testAccount->markHubItemRead(_testAccount->categoryId(), itemId);
            }
            else if(action == "bb.action.MARKREAD")
            {
                _testAccount->markHubItemRead(_testAccount->categoryId(), itemId);
            }
            else if(action == "bb.action.MARKUNREAD")
            {
                _testAccount->markHubItemUnread(_testAccount->categoryId(), itemId);
            }
            else if(action == "bb.action.DELETE")
            {
               _testAccount->removeHubItem(_testAccount->categoryId(), itemId);
            }
            else if(request.action().compare("bb.action.DELETEPRIOR") == 0)
            {
                JsonDataAccess jda;

                qint64 timestamp = (jda.loadFromBuffer(request.data())).toLongLong();
                QDateTime date = QDateTime::fromMSecsSinceEpoch(timestamp);
                _testAccount->removeHubItemsBefore(_testAccount->categoryId(), timestamp);
            }
            else if(request.action().compare("bb.action.MARKPRIORREAD") == 0)
            {
                JsonDataAccess jda;

                qint64 timestamp = (jda.loadFromBuffer(request.data())).toLongLong();
                QDateTime date = QDateTime::fromMSecsSinceEpoch(timestamp);

                _testAccount->markHubItemsReadBefore(_testAccount->categoryId(), timestamp);

            }

            attributesMap.clear();
        }

        jda.deleteLater();
        objectMap.clear();
    }

    action.clear();
    data.clear();
}

void Service::notifyHub(QString data, QString accountID, QString from, QString title, QString body, QString page, QString mode, bool force)
{
    QString notifications   = Utilities::get_string_from_file("data/notifications.json");
    QString hub_integration = Utilities::get_string_from_file("data/hub_integration.json");

    QString exempted        = Utilities::get_string_from_file("data/exempted.json");
    QString pro_version     = Utilities::get_string_from_file("data/pro_version.json");
    QString expired         = Utilities::get_string_from_file("data/expired.json");
    QString is_beta         = Utilities::get_string_from_file("data/is_beta.json");

    qDebug() << "#### Service:: exempted: " << exempted << ", pro_version: " << pro_version<< ", expired: " << expired << ", is_beta: " << is_beta;

    QString thePage = "";

    if(page == "chat")
    {
        thePage = "CardChat.qml";

        Utilities::set_string_to_file("true", "data/new_chat_notifications.json");
    }
    else if(page == "announcement")
    {
        thePage = "Announcement.qml";
    }

    QVariantMap* itemMap        = new QVariantMap();
    (*itemMap)["body"]          = body;
    (*itemMap)["thread_id"]     = data;
    (*itemMap)["theAccountID"]  = accountID;
    (*itemMap)["thePage"]       = thePage;

    if(notifications == "true" || notifications == "" || force)
    {
        if(hub_integration == "true" || hub_integration == "" || force)
        {
            _itemCounter++;

            bool returned_value = false;

            if(mode == "update")
            {
                qint64 source_id = data.toLongLong();

                returned_value = _testAccount->updateHubItem(_testAccount->categoryId(), source_id, *itemMap, true);
            }
            else if(mode == "add")
            {
                returned_value = _testAccount->addHubItem(_testAccount->categoryId(), *itemMap, from, title, QDateTime::currentDateTime().toMSecsSinceEpoch(), QString::number(_itemCounter), "", "",  true);
            }

            qDebug() << "*** Service: HUB returned_value: " << returned_value;
        }
        else
        {
            Utilities::notify_regular(title, from);
        }
    }

    delete itemMap;

    data.clear();
    accountID.clear();
    from.clear();
    title.clear();
    body.clear();
}

void Service::initialize()
{
    if(!hub_initialized)
    {
        _initMutex.lock();

        if (!_udsUtil)
        {
            _udsUtil = new UDSUtil(QString("Facebook Messenger"), QString("hubassets"));
        }

        if (!_udsUtil->initialized())
        {
            _udsUtil->initialize();
        }

        if (_udsUtil->initialized() && _udsUtil->registered())
        {
            if (!_hubCache)
            {
                _hubCache = new HubCache(_settings);
            }

            if (!_testAccount)
            {
                _testAccount = new TestAccount(_udsUtil, _hubCache);
            }
        }

        _initMutex.unlock();

        // INITIALIZATIONS HERE

        refresh_timer = new QTimer(this);
        connect(refresh_timer, SIGNAL(timeout()), this, SLOT(timedOut()));
        int interval = Utilities::get_setting("headless_refresh_timer", "30000").toInt();

        NotificationDefaultApplicationSettings notificationSettings;
        notificationSettings.setPreview(NotificationPriorityPolicy::Allow);
        notificationSettings.apply();

        hub_initialized = true;

        // START REFRESHING

        refresh_timer->start(interval);

        refresh_all();

        qDebug() << "#### Service::initialize() initialized " << hub_initialized;
    }
    else
    {
        qDebug() << "#### Service::initialize() already initialized: " << hub_initialized;
    }
}

void Service::timedOut()
{
    refresh_all();
}

Service::~Service()
{
    qDebug() << "#### Service::~Service()";

    if (_testAccount)
    {
        delete _testAccount;
    }

    if (_hubCache)
    {
        delete _hubCache;
    }

    if (_udsUtil)
    {
        delete _udsUtil;
    }

    if (_settings)
    {
        delete _settings;
    }
}
