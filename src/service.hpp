#ifndef SERVICE_H_
#define SERVICE_H_

#include <QObject>
#include <bb/Application>
#include <stdint.h>
#include "UDSUtil.hpp"
#include <bb/pim/unified/unified_data_source.h>
#include "UDSUtil.hpp"
#include "HubCache.hpp"
#include "TestAccount.hpp"
#include <QtNetwork/QNetworkAccessManager>
#include <QTimer>

namespace bb
{
	namespace system
	{
		class InvokeManager;
		class InvokeRequest;
		class InvokeTargetReply;
		class ApplicationStartupMode;
	}
}

using bb::Application;
using bb::system::ApplicationStartupMode;
using bb::system::InvokeManager;
using bb::system::InvokeRequest;
using bb::system::InvokeTargetReply;

class Service: public QObject
{
	Q_OBJECT

public:

	Service(bb::Application * app);
	virtual ~Service();

	void initialize();

	Q_SLOT void onInvoked(const bb::system::InvokeRequest& request);

	Q_INVOKABLE void notifyHub(QString data, QString accountID, QString from, QString title, QString body, QString page, QString mode, bool force);
	Q_INVOKABLE void request(QString full_url, QString endpoint);
    Q_INVOKABLE void refresh_all();
    Q_INVOKABLE bool thread_exists(QString id);

Q_SIGNALS:

    void complete(QString response, QString httpcode, QString endpoint, QString identifier);

public slots:

    void onComplete();
    void timedOut();

private:

    int  _itemCounter;

    bb::system::InvokeManager * _invokeManager;

	TestAccount*  _testAccount;
	HubCache*     _hubCache;
	UDSUtil*      _udsUtil;
	QSettings*    _settings;
	QMutex        _initMutex;
	Application*  _app;

	QNetworkAccessManager networkAccessManager;
    QTimer *refresh_timer;
};

#endif /* SERVICE_H_ */
