QT       += core network

QT       -= gui

TARGET = NetworkSystem
TEMPLATE = lib
CONFIG += staticlib c++11

SOURCES += NetworkSystem.cpp \
    Server.cpp \
    Connection.cpp \
    WebSocketWrapper.cpp \
    WebSocketServerWrapper.cpp \
    Message.cpp \
    MessagesQueue.cpp

HEADERS += NetworkSystem.h \
    Server.h \
    Connection.h \
    WebSocketWrapper.h \
    WebSocketServerWrapper.h \
    Message.h \
    MessagesQueue.h

# QtWebsocket
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../QtWebsocket/QtWebsocket/release/ -lQtWebsocket
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../QtWebsocket/QtWebsocket/debug/ -lQtWebsocket
else:unix: LIBS += -L$$OUT_PWD/../../QtWebsocket/QtWebsocket/ -lQtWebsocket

INCLUDEPATH += $$PWD/../../QtWebsocket/QtWebsocket
DEPENDPATH += $$PWD/../../QtWebsocket/QtWebsocket

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../QtWebsocket/QtWebsocket/release/libQtWebsocket.a
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../QtWebsocket/QtWebsocket/debug/libQtWebsocket.a
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../QtWebsocket/QtWebsocket/libQtWebsocket.a
