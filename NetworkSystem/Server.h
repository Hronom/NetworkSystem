#ifndef SERVER_H
#define SERVER_H

#include <QThread>

#include "WebSocketServerWrapper.h"
#include "Connection.h"

class Server
{
private:
    QThread *m_serversThread;

    WebSocketServerWrapper *m_webSocketServerWrapper;

public:
    Server(QThread *par_serversThread);
    ~Server();

    bool start(const quint16 &par_port);

    bool hasPendingConnections();
    Connection* nextPendingConnection();

private:
};

#endif
