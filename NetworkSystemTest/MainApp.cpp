#include "MainApp.h"

#include "NetworkSystem.h"
#include "Message.h"

#include <QJsonDocument>
#include <QTimerEvent>
#include <QAbstractSocket>

#include <iostream>

MainApp::MainApp(QObject *parent): QObject(parent)
{
    startTimer(0);
}

MainApp::~MainApp()
{
}

void MainApp::timerEvent(QTimerEvent *event)
{
    killTimer(event->timerId());

    std::cout << "Initialize NetworkSystem => " << NetworkSystem::initialize() << std::endl;

    std::cout << "Server = 1" << std::endl << "Client = 2" << std::endl;
    int value;
    std::cin >> value;

    if(value == 1)
        initServer();
    else if(value == 2)
        initClient();
}

void MainApp::initServer()
{
    std::cout << "Enter port: ";
    quint16 port;
    std::cin >> port;

    Server *server;
    server = NetworkSystem::instance()->createServer();
    std::cout << "Is server listing => " << server->start(port) << std::endl;

    QVector<Connection*> connections;

    while(true)
    {
        if(server->hasPendingConnections())
        {
            connections.append(server->nextPendingConnection());
            std::cout << "new incoming connection" << std::endl;
        }

        // Check for new messages
        {
            QVector<Connection*>::Iterator iter;
            iter = connections.begin();
            while(iter != connections.end())
            {
                Connection *connection;
                connection = (*iter);

                while(connection->hasMessages())
                {
                    Message message;
                    message = connection->nextMessage();

                    QJsonDocument doc;
                    doc.setObject(message.getData());

                    std::cout << doc.toJson().data() << std::endl;
                }

                ++iter;
            }
        }

        // Check for disconnected WebSockets
        {
            QVector<Connection*>::Iterator iter;
            iter = connections.begin();
            while(iter != connections.end())
            {
                Connection *connection;
                connection = (*iter);

                if( connection->state() == QAbstractSocket::UnconnectedState )
                {
                    std::cout << "Connection lost" << std::endl;
                    NetworkSystem::instance()->destroyConnection((*iter));
                    iter = connections.erase(iter);
                }
                else
                    ++iter;
            }
        }
    }
}

void MainApp::initClient()
{
    std::cout << "Enter address: ";
    std::string address;
    std::cin >> address;

    std::cout << "Enter port: ";
    quint16 port;
    std::cin >> port;

    Connection *connection;
    connection = NetworkSystem::instance()->createConnection();
    connection->connectToHost(QString(address.c_str()), port);

    while(connection->state() != QAbstractSocket::ConnectedState)
    {
        std::cout << "connecting..." << std::endl;
    }

    while(true)
    {
        std::cout << "Enter data: ";
        std::string data;
        std::cin >> data;

        QJsonObject dataObject;
        dataObject.insert("message_text", QString::fromStdString(data));

        Message message;
        message.setData(dataObject);

        connection->addMessage(message);
        connection->sendMessages();
    }
}
