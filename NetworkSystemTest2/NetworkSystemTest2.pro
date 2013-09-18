QT       += core network

QT       -= gui

TARGET = NetworkSystemTest2
CONFIG   += console c++11
CONFIG   -= app_bundle

TEMPLATE = app

HEADERS += MainApp.h

SOURCES += main.cpp \
    MainApp.cpp

# NetworkSystem
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../NetworkSystem/release/ -lNetworkSystem
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../NetworkSystem/debug/ -lNetworkSystem
else:unix: LIBS += -L$$OUT_PWD/../NetworkSystem/ -lNetworkSystem

INCLUDEPATH += $$PWD/../NetworkSystem
DEPENDPATH += $$PWD/../NetworkSystem

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../NetworkSystem/release/libNetworkSystem.a
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../NetworkSystem/debug/libNetworkSystem.a
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../NetworkSystem/libNetworkSystem.a

# QtWebsocket
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../QtWebsocket/QtWebsocket/release/ -lQtWebsocket
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../QtWebsocket/QtWebsocket/debug/ -lQtWebsocket
else:unix: LIBS += -L$$OUT_PWD/../../QtWebsocket/QtWebsocket/ -lQtWebsocket

INCLUDEPATH += $$PWD/../../QtWebsocket/QtWebsocket
DEPENDPATH += $$PWD/../../QtWebsocket/QtWebsocket

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../QtWebsocket/QtWebsocket/release/libQtWebsocket.a
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../QtWebsocket/QtWebsocket/debug/libQtWebsocket.a
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../QtWebsocket/QtWebsocket/libQtWebsocket.a
