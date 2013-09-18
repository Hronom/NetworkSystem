#ifndef WEBSOCKETSERVERWRAPPER_H
#define WEBSOCKETSERVERWRAPPER_H

#include <QObject>

#include "QWsServer.h"

#include "Connection.h"

class WebSocketServerWrapper: public QObject
{
    Q_OBJECT
private:
    QtWebsocket::QWsServer *m_webSocketServer;

    QThread *m_origThread;

    QQueue<QtWebsocket::QWsSocket*> m_pendingConnections;

public:
    WebSocketServerWrapper();
    virtual ~WebSocketServerWrapper();

    Q_INVOKABLE void initialize();
    Q_INVOKABLE void deinitialize();

    Q_INVOKABLE bool listen(const quint16 &par_port);
    Q_INVOKABLE bool hasPendingConnections();
    Q_INVOKABLE QtWebsocket::QWsSocket* nextPendingConnection();
};

#endif
