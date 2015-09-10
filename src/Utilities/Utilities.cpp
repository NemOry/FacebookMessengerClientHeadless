#include "Utilities.hpp"

#include <bb/platform/Notification>
#include <bb/system/InvokeManager>
#include <sys/procfs.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdint.h>

using namespace bb::platform;

const QString AUTHOR_NAME           = "NEMORYSTUDIOS";
const QString APP_NAME              = "MESSENGER";
const QString HEADLESS_TARGET_ID    = "lcom.nemory.fbmessenger.headless";
const QString UI_TARGET_ID          = "lcom.nemory.fbmessenger";

const QString _MY_MESSENGER_ID      = "508427445917366";
const QString _MACADAMIAN_ID        = "583669825050238";
const QString _GOCHAT_ID            = "138055292887831";

const QString FB_APP_ID             = _MACADAMIAN_ID;

Utilities::Utilities(QObject* parent) : QObject(parent)
{

}

void Utilities::notify_regular(QString title, QString message)
{
    QString notificationsString = get_string_from_file("data/notifications.json");

    qDebug() << "#### Service::notify_regular notificationsString: " + notificationsString + ", title: " + title + ", message: " + message;

    if(notificationsString == "true")
    {
        Notification* notification = new Notification();
        notification->setTitle(title);
        notification->setBody(message);
        notification->setIconUrl(QUrl("app/native/assets/media/images/icons/114.png")) ;

        bb::system::InvokeRequest invokeRequest;
        invokeRequest.setTarget(ui_target_id());
        invokeRequest.setAction("bb.action.OPEN");
        invokeRequest.setMimeType("text/plain");

        notification->setInvokeRequest(invokeRequest);
        notification->notify();

        delete notification;
    }
}

void Utilities::set_string_to_file(QString log, QString fileName)
{
    QFile file(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << log;
    file.close();
    file.deleteLater();
    fileName.clear();
    log.clear();
    out.flush();
}

QString Utilities::fb_app_id()
{
    return FB_APP_ID;
}

QString Utilities::author_name()
{
    return AUTHOR_NAME;
}

QString Utilities::app_name()
{
    return APP_NAME;
}

QString Utilities::headless_target_id()
{
    return HEADLESS_TARGET_ID;
}

QString Utilities::ui_target_id()
{
    return UI_TARGET_ID;
}

QString Utilities::get_string_from_file(QString fileName)
{
    QString fileString = "";

    QFile theFile(fileName);

    if(theFile.open(QIODevice::ReadOnly))
    {
        QTextStream fileBytes(&theFile);
        fileString = fileBytes.readAll();
        fileBytes.flush();
    }

    theFile.close();
    theFile.deleteLater();
    fileName.clear();

    return fileString;
}

QString Utilities::get_setting(QString key, QString default_value)
{
	QSettings settings(AUTHOR_NAME, APP_NAME);

	if (settings.value(key).isNull() || settings.value(key) == "")
	{
		return default_value;
	}

	QString value = settings.value(key).toString();

	settings.deleteLater();

	return value;
}

void Utilities::set_setting(QString key, QString value)
{
	QSettings settings(AUTHOR_NAME, APP_NAME);
	settings.setValue(key, QVariant(value));
	settings.deleteLater();
}

void Utilities::delete_file(QString file_name)
{
    if(QFile::exists(file_name))
    {
        QFile::remove(file_name);
    }
}

void Utilities::wipe_folder_contents(QString folder)
{
    if(folder.length() > 0)
    {
        QDir dir(folder);

        if (dir.exists(folder))
        {
            Q_FOREACH(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files | QDir::AllEntries | QDir::Writable, QDir::DirsFirst))
            {
                if (info.isDir())
                {
                    wipe_folder(info.absoluteFilePath());
                }
                else
                {
                    QFile::remove(info.absoluteFilePath());
                }
            }
        }
    }
}

void Utilities::wipe_folder(QString folder)
{
    if(folder.length() > 0)
    {
        QDir dir(folder);

        if (dir.exists(folder))
        {
            Q_FOREACH(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files | QDir::AllEntries | QDir::Writable, QDir::DirsFirst))
            {
                if (info.isDir())
                {
                    wipe_folder(info.absoluteFilePath());
                }
                else
                {
                    QFile::remove(info.absoluteFilePath());
                }
            }
        }
    }
}

qint64 Utilities::get_folder_size(QString folder_path)
{
    qint64 total_size = 0;

    QDir files_directory(folder_path);

    if (files_directory.exists(folder_path))
    {
        Q_FOREACH(QFileInfo info, files_directory.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files | QDir::AllEntries | QDir::Writable, QDir::DirsFirst))
        {
            QFile file(info.absoluteFilePath());

            if(file.open(QIODevice::ReadWrite))
            {
                total_size = total_size + file.size();
            }

            file.close();
        }
    }

    return total_size;
}

qint64 Utilities::get_cache_size()
{
    QString wallpapers          = QDir::homePath() + "/Cache/wallpapers/";
    QString images              = QDir::homePath() + "/Cache/images/";

    qint64 total_size = (get_folder_size(wallpapers) + get_folder_size(images));

    return total_size;
}

bool Utilities::contains(QString text, QString find)
{
    return text.contains(find, Qt::CaseInsensitive);
}

void Utilities::clear_notification_effects()
{
   Notification::clearEffectsForAll();
}

void Utilities::clear_notifications()
{
   Notification::clearEffectsForAll();
   Notification::deleteAllFromInbox();
}

QString Utilities::regex(QString text, QString expression, int index)
{
    QRegExp rxItem(expression);
    QString result = "";

    if( rxItem.indexIn( text ) != -1 )
    {
        result = rxItem.cap(index);
    }

    return result;
}

void Utilities::copy_file(QString from, QString to)
{
    if(QFile::exists(to)) // OVERRIDE
    {
        QFile::remove(to);
    }

    if(QFile::exists(from))
    {
        if(QFile::copy(from, to))
        {
            qDebug() << "SUCCESSFULLY COPIED from: " + from + ", to: " + to;
        }
        else
        {
            qDebug() << "FAILED TO COPY 2 from: " + from + ", to: " + to;
        }
    }
    else
    {
        qDebug() << "FAILED TO COPY 1 from: " + from + ", to: " + to;
    }
}

void Utilities::copy_and_remove_file(QString from, QString to)
{
    if(QFile::exists(from))
    {
        if(QFile::exists(to))
        {
            QFile::remove(to);
        }

        if(QFile::copy(from, to))
        {
            QFile::remove(from);
        }
    }
}
