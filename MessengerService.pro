APP_NAME = MessengerService

CONFIG 	+= qt warn_on

QT 		+= network
QT 		+= declarative
QT 		+= xml

LIBS 	+= -lbb -lbbsystem -lbbplatform -lbbdata -lbbnetwork -lunifieddatasourcec -lbbpim

include(config.pri)
