#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <QtCore/QObject>
#include <QtCore/QFile>
#include <QtCore/QtCore>
#include <stdint.h>

class Utilities : public QObject
{
    Q_OBJECT

public:
    Utilities(QObject* parent = 0);

    Q_INVOKABLE static QString author_name();
    Q_INVOKABLE static QString app_name();
    Q_INVOKABLE static QString fb_app_id();
    Q_INVOKABLE static QString headless_target_id();
    Q_INVOKABLE static QString ui_target_id();

    Q_INVOKABLE static void copy_and_remove_file(QString from, QString to);
    Q_INVOKABLE static void copy_file(QString from, QString to);
    Q_INVOKABLE static QString regex(QString text, QString expression, int index);
    Q_INVOKABLE static void clear_notifications();
    Q_INVOKABLE static void clear_notification_effects();
    Q_INVOKABLE static qint64 get_cache_size();
    Q_INVOKABLE static qint64 get_folder_size(QString folder_path);

    Q_INVOKABLE static bool contains(QString text, QString find);
    Q_INVOKABLE static void notify_regular(QString title, QString message);
    Q_INVOKABLE static void set_string_to_file(QString log, QString file_name);
    Q_INVOKABLE static QString get_string_from_file(QString file_name);
    Q_INVOKABLE static QString get_setting(QString key, QString default_value);
	Q_INVOKABLE static void set_setting(QString key, QString value);
	Q_INVOKABLE static void delete_file(QString file_name);
	Q_INVOKABLE static void wipe_folder(QString folder);
    Q_INVOKABLE static void wipe_folder_contents(QString folder);

};

#endif /* UTILITIES_H_ */

