//#ifndef SERVICE_H_
//#define SERVICE_H_
//
//#include <QObject>
//#include <bb/Application>
//#include <stdint.h>
//#include "UDSUtil.hpp"
//#include <bb/pim/unified/unified_data_source.h>
//#include "UDSUtil.hpp"
//#include "HubCache.hpp"
//#include "TestAccount.hpp"
//
//#include "src/qxmpp/client/QXmppClient.h"
//
//namespace bb
//{
//	namespace system
//	{
//		class InvokeManager;
//		class InvokeRequest;
//		class InvokeTargetReply;
//		class ApplicationStartupMode;
//	}
//}
//
//using bb::Application;
//using bb::system::ApplicationStartupMode;
//using bb::system::InvokeManager;
//using bb::system::InvokeRequest;
//using bb::system::InvokeTargetReply;
//
//class Service: public QObject
//{
//	Q_OBJECT
//
//public:
//
//	Service(bb::Application * app);
//	virtual ~Service();
//
//	void initialize();
//
//	Q_SLOT void onInvoked(const bb::system::InvokeRequest& request);
//
//	Q_INVOKABLE void notifyHub(QString data, QString accountID, QString from, QString title, QString body, QString pageName, bool force);
//
//	Q_INVOKABLE void login_natively(QString username, QString password);
//    Q_INVOKABLE void login(QString access_token);
//    Q_INVOKABLE void logout();
//    Q_INVOKABLE void sendMessage(QString from, QString to, QString message);
//    Q_INVOKABLE QString timeSince(qint64 time);
//    Q_INVOKABLE void parse_all_friends();
//
//private slots:
//
//    void messageReceived(const QXmppMessage&);
//    void messageAcknowledged(const QXmppMessage&, const bool value);
//    void onError(QXmppClient::Error);
//    void clientConnected();
//    void clientDisconnected();
//
//private:
//
//    bb::system::InvokeManager * _invokeManager;
//
//    int  _itemCounter;
//
//    QVariantMap all_friends_object_map;
//    bool all_friends_object_map_valid;
//
//	TestAccount*  _testAccount;
//	HubCache*     _hubCache;
//	UDSUtil*      _udsUtil;
//	QSettings*    _settings;
//	QMutex        _initMutex;
//	Application*  _app;
//
//	QXmppClient* client;
//
//    bool _connected;
//};
//
//#endif /* SERVICE_H_ */
