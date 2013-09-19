#include "WebSocketServerWrapper.h"

WebSocketServerWrapper::WebSocketServerWrapper(): QObject(0)
{
    m_origThread = this->thread();
}

WebSocketServerWrapper::~WebSocketServerWrapper()
{

}

void WebSocketServerWrapper::initialize()
{
    m_webSocketServer = new QtWebsocket::QWsServer();
}

void WebSocketServerWrapper::deinitialize()
{
    delete m_webSocketServer;
}

bool WebSocketServerWrapper::listen(const quint16 &par_port)
{
    return m_webSocketServer->listen(QHostAddress::Any, par_port);
}

bool WebSocketServerWrapper::hasPendingConnections()
{
    return m_webSocketServer->hasPendingConnections();
}

QtWebsocket::QWsSocket* WebSocketServerWrapper::nextPendingConnection()
{
    if(m_webSocketServer->hasPendingConnections())
    {
        QtWebsocket::QWsSocket *socket;
        socket = m_webSocketServer->nextPendingConnection();
        socket->setParent(0);
        socket->moveToThread(m_origThread);
        return socket;
    }
    else
        return 0;
}
