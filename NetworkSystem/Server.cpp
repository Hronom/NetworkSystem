#include "Server.h"

#include "NetworkSystem.h"
#include <QMetaObject>
#include <QDebug>

Server::Server(QThread *par_serversThread)
{
    m_serversThread = par_serversThread;

    m_webSocketServerWrapper = new WebSocketServerWrapper();
    m_webSocketServerWrapper->moveToThread(m_serversThread);
    QMetaObject::invokeMethod(m_webSocketServerWrapper,
                              "initialize",
                              Qt::BlockingQueuedConnection);
}

Server::~Server()
{
    QMetaObject::invokeMethod(m_webSocketServerWrapper,
                              "deinitialize",
                              Qt::BlockingQueuedConnection);
    delete m_webSocketServerWrapper;
}

bool Server::start(const quint16 &par_port)
{
    bool started = false;
    QMetaObject::invokeMethod(m_webSocketServerWrapper,
                              "listen",
                              Qt::BlockingQueuedConnection,
                              Q_RETURN_ARG(bool, started),
                              Q_ARG(quint16, par_port));

    if(started == false)
        qDebug()<<"Server start fail";
    else
        qDebug()<<"Server started at port:"<<par_port;
    return started;
}

bool Server::hasPendingConnections()
{
    bool hasPendingConnections;
    hasPendingConnections = false;
    QMetaObject::invokeMethod(m_webSocketServerWrapper,
                              "hasPendingConnections",
                              Qt::BlockingQueuedConnection,
                              Q_RETURN_ARG(bool, hasPendingConnections));
    return hasPendingConnections;
}

Connection* Server::nextPendingConnection()
{
    QtWebsocket::QWsSocket *wsSocket;
    wsSocket = 0;

    QMetaObject::invokeMethod(m_webSocketServerWrapper,
                              "nextPendingConnection",
                              Qt::BlockingQueuedConnection,
                              Q_RETURN_ARG(QtWebsocket::QWsSocket*, wsSocket));

    if(wsSocket != 0)
    {
        Connection *connection;
        connection = NetworkSystem::instance()->createConnection(wsSocket);
        return connection;
    }
    else
        return 0;
}
