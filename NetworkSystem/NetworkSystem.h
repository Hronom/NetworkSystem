#ifndef NETWORKSYSTEM_H
#define NETWORKSYSTEM_H

#include <QObject>

#include <QThread>
#include <QList>
#include <QHostAddress>

#include "Server.h"
#include "Connection.h"

class NetworkSystem
{
private:
    static NetworkSystem* m_instance;

    QThread *m_serversThread;
    QThread *m_connectionsThread;

    QList<Server*> m_servers;
    QList<Connection*> m_connections;

public:
    static bool initialize();
    static void shutdown();
    static NetworkSystem* instance();
    
private:
    NetworkSystem();
    ~NetworkSystem();
    bool init();

public:
    void injectUpdate(const float& par_timeSinceLastUpdate);

    Server* createServer();
    void destroyServer(Server *par_server);

    Connection* createConnection();
    Connection* createConnection(QtWebsocket::QWsSocket *par_wsSocket);
    void destroyConnection(Connection *par_connection);

    QList<QHostAddress> getHostAddresses();
};

#endif // NETWORKSYSTEM_H
