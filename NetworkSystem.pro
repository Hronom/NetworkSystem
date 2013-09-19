TEMPLATE = subdirs

#CONFIG += ordered

SUBDIRS += \
    QtWebsocket \
    NetworkSystem \
    NetworkSystemTest \
    NetworkSystemTest2

NetworkSystem.depends = QtWebsocket

NetworkSystemTest.depends = NetworkSystem

NetworkSystemTest2.depends = NetworkSystem
