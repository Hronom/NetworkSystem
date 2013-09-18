#include "NetworkSystem.h"

#include <QCoreApplication>
#include <QNetworkInterface>
#include <QDebug>

NetworkSystem* NetworkSystem::m_instance = 0;

bool NetworkSystem::initialize()
{
    qDebug()<<"Initialize:"<<"NetworkSystem";
    m_instance = new NetworkSystem();
    return m_instance->init();
}

void NetworkSystem::shutdown()
{
    qDebug()<<"Shutdown:"<<"NetworkSystem";
    delete m_instance;
    m_instance = 0;
}

NetworkSystem* NetworkSystem::instance()
{
    return m_instance;
}

NetworkSystem::NetworkSystem()
{
    m_serversThread = new QThread();
    m_connectionsThread = new QThread();
}

NetworkSystem::~NetworkSystem()
{
    m_serversThread->quit();
    while(!m_serversThread->isFinished());
    delete m_serversThread;

    m_connectionsThread->quit();
    while(!m_connectionsThread->isFinished());
    delete m_connectionsThread;
}

bool NetworkSystem::init()
{
    m_serversThread->start();
    m_connectionsThread->start();

    return true;
}

void NetworkSystem::injectUpdate(const float &par_timeSinceLastUpdate)
{
    Q_UNUSED(par_timeSinceLastUpdate)
    QCoreApplication::processEvents();
}

Server *NetworkSystem::createServer()
{
    Server *server;
    server = new Server(m_serversThread);

    m_servers.append(server);

    return server;
}

void NetworkSystem::destroyServer(Server *par_server)
{
    m_servers.removeOne(par_server);
    delete par_server;
}

Connection* NetworkSystem::createConnection()
{
    Connection *connection;
    connection = new Connection(m_connectionsThread);

    m_connections.append(connection);

    return connection;
}

Connection* NetworkSystem::createConnection(QtWebsocket::QWsSocket *par_wsSocket)
{
    Connection *connection;
    connection = new Connection(m_connectionsThread, par_wsSocket);

    m_connections.append(connection);

    return connection;
}

void NetworkSystem::destroyConnection(Connection *par_connection)
{
    m_connections.removeOne(par_connection);
    delete par_connection;
}

QList<QHostAddress> NetworkSystem::getHostAddresses()
{
    return QNetworkInterface::allAddresses();
}
