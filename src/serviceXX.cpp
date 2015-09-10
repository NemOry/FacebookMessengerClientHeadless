//#include <src/Utilities/Utilities.hpp>
//#include <stdint.h>
//#include "service.hpp"
//
//#include <bb/Application>
//#include <bb/platform/Notification>
//#include <bb/platform/NotificationDefaultApplicationSettings>
//#include <bb/system/InvokeManager>
//#include <bb/data/JsonDataAccess>
//#include <QUrl>
//#include <QtNetwork/QtNetwork>
//
//#include <iostream>
//#include <QBuffer>
//#include <QDir>
//#include <QFile>
//#include <QXmlStreamWriter>
//
//#include "src/qxmpp/client/QXmppRosterManager.h"
//#include "src/qxmpp/base/QXmppVCardIq.h"
//#include "src/qxmpp/client/QXmppVCardManager.h"
//#include "src/qxmpp/client/QXmppClient.h"
//#include "src/qxmpp/base/QXmppLogger.h"
//#include "src/qxmpp/base/QXmppMessage.h"
//#include "src/qxmpp/client/QXmppConfiguration.h"
//
//using bb::data::JsonDataAccess;
//using namespace bb::platform;
//using namespace bb::system;
//
//const QString AUTHOR 		    = "NEMORY";
//const QString APPNAME 		    = "MESSENGER";
//
//bool firstInstalled             = true;
//bool hub_initialized            = false;
//
//#define ARRAY_SIZE(arr) ((sizeof(arr))/(sizeof(arr[0])))
//
//const QString _ANDROID_ID       = "882a8490361da98702bf97a021ddc14d";
//const QString _BLACKBERRY_ID    = "2254487659";
//const QString _IPHONE_ID        = "3e7c78e35a76a9299309885393b02d97";
//const QString _IPAD_ID          = "350939045778";
//const QString _IPOD_ID          = "4df3200f360533d57e0353bed01109d8";
//
//Service::Service(bb::Application * app)	:
//		_invokeManager(new InvokeManager()),
//		_testAccount(NULL),
//		_hubCache(NULL),
//		_udsUtil(NULL),
//		_settings(NULL),
//		_app(app)
//{
//    bool started = false;
//    all_friends_object_map_valid = false;
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
//}
//
//void Service::parse_all_friends()
//{
//    QString all_friends_keyvalue_pair = Utilities::get_string_from_file("data/all_friends_keyvalue_pair.json");
//
//    if(all_friends_keyvalue_pair.length() > 0)
//    {
//        JsonDataAccess jda;
//
//        all_friends_object_map = jda.loadFromBuffer(all_friends_keyvalue_pair).toMap();
//
//        if(!jda.hasError())
//        {
//            all_friends_object_map_valid = true;
//        }
//        else
//        {
//            all_friends_object_map_valid = false;
//        }
//
//        jda.deleteLater();
//    }
//    else
//    {
//        all_friends_object_map_valid = false;
//    }
//
//    qDebug() << "all_friends_keyvalue_pair.length: " << all_friends_keyvalue_pair.length() << ", all_friends_object_map_valid: " << all_friends_object_map_valid;
//}
//
//void Service::logout()
//{
//    if(client != NULL)
//    {
//        qDebug() << "#### Service:: LOGGING OUT ***";
//
//        client->disconnectFromServer();
//    }
//}
//
//void Service::login_natively(QString username, QString password)
//{
//    qDebug() << "#### Service:: LOGGING IN NATIVELY: username" << username << ", password: " << password << " ***";
//
//
//    QXmppConfiguration configuration;
//    //configuration.setFacebookAccessToken(access_token);
//    configuration.setUser(username);
//    configuration.setPassword(password);
//    configuration.setDomain("chat.facebook.com");
//    configuration.setHost("chat.facebook.com");
//    configuration.setAutoReconnectionEnabled(true);
//    //configuration.setFacebookAppId(Utilities::fb_app_id());
//    configuration.setFacebookAppId(_ANDROID_ID);
//
//    QXmppPresence presence;
//    client->connectToServer(configuration, presence);
//}
//
//void Service::login(QString access_token)
//{
//    qDebug() << "#### Service:: LOGGING IN: access_token" << access_token << " ***";
//
//    QXmppConfiguration configuration;
//    configuration.setFacebookAccessToken(access_token);
//    configuration.setDomain("chat.facebook.com");
//    configuration.setHost("chat.facebook.com");
//    configuration.setFacebookAppId(Utilities::fb_app_id());
//    configuration.setAutoReconnectionEnabled(true);
//    //configuration.setFacebookAppId(_ANDROID_ID);
//
//    QXmppPresence presence;
//    client->connectToServer(configuration, presence);
//}
//
//void Service::sendMessage(QString from, QString to, QString message)
//{
//    qDebug() << "#### Service:: SENDING MESSAGE: message: " << message << ", to: " << to << " ***";
//
//    client->sendPacket(QXmppMessage("-" + from + "@chat.facebook.com", "-" + to + "@chat.facebook.com", message));
//}
//
//void Service::clientConnected()
//{
//    qDebug() << "#### Service:: CONNECTED *** access_token: " << client->configuration().facebookAccessToken() << ", APP ID: " << client->configuration().facebookAppId() << ", user: " << client->configuration().user();
//
//    _connected = true;
//}
//
//void Service::clientDisconnected()
//{
//    qDebug() << "#### Service:: DISCONNECTED ***";
//
//    _connected = false;
//
//    QString access_token = Utilities::get_string_from_file("data/current_access_token.txt");
//
//    if(access_token.length() > 0)
//    {
//        login(access_token);
//
//        qDebug() << "#### Service:: RECONNECTING ***";
//    }
//}
//
//void Service::onError(QXmppClient::Error errorObject)
//{
//    QString errorMessage = "";
//
//    if (errorObject == QXmppClient::XmppStreamError && client->xmppStreamError() == QXmppStanza::Error::NotAuthorized)
//    {
//        errorMessage = "* Authentication Failed *\n- Please make sure you allowed the 'Send and Receive Messages (xmpp_login)' Permission. If this is the case, just re-login your accounts.\n\n===== OR =====\n\n- If you're new to version 5.0.400 and above, we've implemented new things so we need to require you to Uninstall and Reinstall this app. \n\nThank you very much and we apologize for the hassle.";
//    }
//
//    qDebug() << "#### Service:: ERROR " << errorObject << ", xmpp_stream_error: " << client->xmppStreamError() << " ***";
//
//    //emit error(errorObject, errorMessage);
//}
//
//void Service::messageAcknowledged(const QXmppMessage& xmppmessage, const bool value)
//{
//    qDebug() << "#### Service:: messageAcknowledged, value: " << value;
//}
//
//void Service::messageReceived(const QXmppMessage& xmppmessage)
//{
//    QString id                      = xmppmessage.id();
//    QString from                    = xmppmessage.from();
//    QString message                 = xmppmessage.body();
//    QString from_id                 = Utilities::regex(from, "-(.*)@chat.facebook.com", 1);
//
//    if(xmppmessage.type() == 3)
//    {
//        qDebug() << "#### Service:: GROUP CHAT MESSAGE RECEIVED ***";
//    }
//
//    if(xmppmessage.body().length() > 0)
//    {
//        QVariantMap fromObject;
//        fromObject["id"]                = from_id;
//
//        if(all_friends_object_map_valid)
//        {
//            fromObject["name"]          = all_friends_object_map[from_id].toString();
//        }
//
//        if(fromObject["name"].toString().length() == 0)
//        {
//            fromObject["name"] = "New Message";
//        }
//
//        QVariantMap messageObject;
//        messageObject["id"]             = id;
//        messageObject["from"]           = fromObject;
//        messageObject["message"]        = message;
//        messageObject["created_time"]   = QDateTime::currentMSecsSinceEpoch();
//
//        notifyHub(from_id, Utilities::get_string_from_file("data/current_user_id.txt"), fromObject["name"].toString(), fromObject["name"].toString(), message, "chat", false);
//
//        qDebug() << "#### Service:: MESSAGE RECEIVED: from: " << xmppmessage.from() << ", from_id: " << from_id << ", body: " << xmppmessage.body() << ", all_friends_object_map_valid: " << all_friends_object_map_valid << ", from_name: " << fromObject["name"].toString() << " ***";
//    }
//}
//
//QString Service::timeSince(qint64 time)
//{
//   QString periods[] = {"s", "m", "h", "d", "w", "mo", "y", "dec"};
//
//   int lengths[] = {60, 60, 24, 7, 4.35, 12, 10};
//
//   qint64 now = QDateTime::currentMSecsSinceEpoch() / 1000;
//
//   qint64 difference     = now - (time / 1000);
//   QString tense         = "ago";
//
//   int j = 0;
//
//   for(j = 0; difference >= lengths[j] && j < ARRAY_SIZE(lengths) - 1; j++)
//   {
//       difference /= lengths[j];
//   }
//
//   difference = qRound(difference);
//
//   return QString::number(difference) + "" + periods[j] + " " + tense;
//}
//
//void Service::notifyHub(QString data, QString accountID, QString from, QString title, QString body, QString pageName, bool force)
//{
//    QString notifications   = Utilities::get_string_from_file("data/notifications.json");
//    QString hub_integration = Utilities::get_string_from_file("data/hub_integration.json");
//
//    QString exempted        = Utilities::get_string_from_file("data/exempted.json");
//    QString pro_version     = Utilities::get_string_from_file("data/pro_version.json");
//    QString expired         = Utilities::get_string_from_file("data/expired.json");
//    QString is_beta         = Utilities::get_string_from_file("data/is_beta.json");
//
//    qDebug() << "#### Service:: exempted: " << exempted << ", pro_version: " << pro_version<< ", expired: " << expired << ", is_beta: " << is_beta;
//
//    QString thePage = "";
//
//    if(pageName == "chat")
//    {
//        thePage = "CardChat.qml";
//
//        Utilities::set_string_to_file("true", "data/new_chat_notifications.json");
//    }
//    else if(pageName == "announcement")
//    {
//        thePage = "Announcement.qml";
//    }
//
//    QVariantMap* itemMap        = new QVariantMap();
//    (*itemMap)["body"]          = body;
//    (*itemMap)["theData"]       = data;
//    (*itemMap)["theAccountID"]  = accountID;
//    (*itemMap)["thePage"]       = thePage;
//
//    if(notifications == "true" || notifications == "" || force)
//    {
//        if(hub_integration == "true" || hub_integration == "" || force)
//        {
//            //_testAccount->updateHubItem(_testAccount->categoryId(), , *itemMap, true);
//
////            if()
////            {
////                bool retVal = _testAccount->addHubItem(_testAccount->categoryId(), *itemMap, from, title, QDateTime::currentDateTime().toMSecsSinceEpoch(), QString::number(_itemCounter), "", "",  true);
////            }
////            else
////            {
////                bool retVal = _testAccount->addHubItem(_testAccount->categoryId(), *itemMap, from, title, QDateTime::currentDateTime().toMSecsSinceEpoch(), QString::number(_itemCounter), "", "",  true);
////            }
//
//            bool retVal = _testAccount->addHubItem(_testAccount->categoryId(), *itemMap, from, title, QDateTime::currentDateTime().toMSecsSinceEpoch(), QString::number(_itemCounter), "", "",  true);
//
//            qDebug() << "*** Service: RETURN VALUE: " << retVal;
//        }
//        else
//        {
//            Utilities::notify_regular(title, from);
//        }
//    }
//
//    delete itemMap;
//
//    data.clear();
//    accountID.clear();
//    from.clear();
//    title.clear();
//    body.clear();
//}
//
//void Service::initialize()
//{
//    if(!hub_initialized)
//    {
//        _initMutex.lock();
//
//        if (!_udsUtil)
//        {
//            _udsUtil = new UDSUtil(QString("Messenger"), QString("hubassets"));
//        }
//
//        if (!_udsUtil->initialized())
//        {
//            _udsUtil->initialize();
//        }
//
//        if (_udsUtil->initialized() && _udsUtil->registered())
//        {
//            if (!_hubCache)
//            {
//                _hubCache = new HubCache(_settings);
//            }
//
//            if (!_testAccount)
//            {
//                _testAccount = new TestAccount(_udsUtil, _hubCache);
//            }
//        }
//
//        _initMutex.unlock();
//
//        // INITIALIZATIONS HERE
//
//        NotificationDefaultApplicationSettings notificationSettings;
//        notificationSettings.setPreview(NotificationPriorityPolicy::Allow);
//        notificationSettings.apply();
//
//        hub_initialized = true;
//
//        client = new QXmppClient(this);
//
//        connect(client, SIGNAL(messageReceived(QXmppMessage)), SLOT(messageReceived(QXmppMessage)));
//        connect(client, SIGNAL(connected()), SLOT(clientConnected()));
//        connect(client, SIGNAL(disconnected()), SLOT(clientDisconnected()));
//        connect(client, SIGNAL(error(QXmppClient::Error)), SLOT(onError(QXmppClient::Error)));
//
//        qDebug() << "#### Service::initialize() initialized " << hub_initialized;
//    }
//}
//
//void Service::onInvoked(const bb::system::InvokeRequest& request)
//{
//    initialize();
//
//    QString action  = request.action();
//    QString data    = request.data();
//
//    qDebug() << "#### Service::onInvoked() action: " + action + ", data: " + data;
//
//    if(action == "bb.action.COMMAND")
//    {
//        if(data.contains("new_announcements", Qt::CaseInsensitive))
//        {
//            QString can_announce = Utilities::get_string_from_file("data/can_announce.json");
//
//            if(can_announce == "true")
//            {
//                QString title = "Messenger Announcements";
//                QString message = "Some worthwile announcements from Nemory Studios.";
//
//                notifyHub("", "accountID", title, message, message, "announcement", true);
//
//                Utilities::set_string_to_file("false", "data/can_announce.json");
//            }
//        }
//        else if(data == "update_hub_account")
//        {
//            bool _supportsCompose                   = true;
//
//            QString _displayName                    = "Messenger";
//            QString _description                    = "";
//            QString _serverName                     = "Messenger.com";
//            QString _iconFilename                   = "acc_uncolored.png";
//            QString _lockedIconFilename             = "acc_locked_uncolored.png";
//            QString _composeIconFilename            = "acc_compose_uncolored.png";
//
//            QString _headlessTarget                 = Utilities::headless_target_id();
//            QString hub_account_name                = Utilities::get_string_from_file("data/hub_account_name.json");
//
//            bool result = _udsUtil->updateAccount(_hubCache->accountId(), _displayName, _headlessTarget,
//                                            _iconFilename, _lockedIconFilename, _composeIconFilename, hub_account_name,
//                                            _supportsCompose, UDS_ACCOUNT_TYPE_OTHER);
//        }
//        else if(data == "parse_all_friends")
//        {
//            parse_all_friends();
//        }
//        else if(data == "login")
//        {
//            QString access_token = Utilities::get_string_from_file("data/current_access_token.txt");
//
//            if(access_token.length() > 0)
//            {
//                login(access_token);
//            }
//        }
//        else if(data == "logout")
//        {
//            logout();
//        }
//        else if(data == "check_login")
//        {
//           if(!_connected)
//           {
//               QString access_token = Utilities::get_string_from_file("data/current_access_token.txt");
//
//               if(access_token.length() > 0)
//               {
//                   login(access_token);
//               }
//           }
//        }
//        else if(data == "stop")
//        {
//            _app->requestExit();
//        }
//    }
//    else if(action == "bb.action.STOP")
//    {
//        _app->requestExit();
//    }
//    else
//    {
//        JsonDataAccess jda;
//
//        QVariantMap objectMap = (jda.loadFromBuffer(request.data())).toMap();
//
//        if(!jda.hasError())
//        {
//            QVariantMap attributesMap = objectMap["attributes"].toMap();
//
//            qint64 itemId;
//
//            if (attributesMap["sourceId"].toString().length() > 0)
//            {
//                itemId = attributesMap["sourceId"].toLongLong();
//            }
//            else if (attributesMap["messageid"].toString().length() > 0)
//            {
//                itemId = attributesMap["messageid"].toLongLong();
//            }
//
//            if(action == "bb.action.VIEW")
//            {
//                _testAccount->markHubItemRead(_testAccount->categoryId(), itemId);
//            }
//            else if(action == "bb.action.MARKREAD")
//            {
//                _testAccount->markHubItemRead(_testAccount->categoryId(), itemId);
//            }
//            else if(action == "bb.action.MARKUNREAD")
//            {
//                _testAccount->markHubItemUnread(_testAccount->categoryId(), itemId);
//            }
//            else if(action == "bb.action.DELETE")
//            {
//               _testAccount->removeHubItem(_testAccount->categoryId(), itemId);
//            }
//            else if(request.action().compare("bb.action.DELETEPRIOR") == 0)
//            {
//                JsonDataAccess jda;
//
//                qint64 timestamp = (jda.loadFromBuffer(request.data())).toLongLong();
//                QDateTime date = QDateTime::fromMSecsSinceEpoch(timestamp);
//                _testAccount->removeHubItemsBefore(_testAccount->categoryId(), timestamp);
//            }
//            else if(request.action().compare("bb.action.MARKPRIORREAD") == 0)
//            {
//                JsonDataAccess jda;
//
//                qint64 timestamp = (jda.loadFromBuffer(request.data())).toLongLong();
//                QDateTime date = QDateTime::fromMSecsSinceEpoch(timestamp);
//
//                _testAccount->markHubItemsReadBefore(_testAccount->categoryId(), timestamp);
//
//            }
//
//            attributesMap.clear();
//        }
//
//        jda.deleteLater();
//        objectMap.clear();
//    }
//
//    action.clear();
//    data.clear();
//}
//
//Service::~Service()
//{
//    qDebug() << "#### Service::~Service()";
//
//    if (_testAccount)
//    {
//        delete _testAccount;
//    }
//
//    if (_hubCache)
//    {
//        delete _hubCache;
//    }
//
//    if (_udsUtil)
//    {
//        delete _udsUtil;
//    }
//
//    if (_settings)
//    {
//        delete _settings;
//    }
//}
