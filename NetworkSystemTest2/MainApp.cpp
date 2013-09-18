#include "MainApp.h"

#include "NetworkSystem.h"
#include "Message.h"

#include <QTimerEvent>
#include <QCoreApplication>
#include <QElapsedTimer>
#include <QJsonDocument>
#include <QDebug>

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

    initClient();
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
        std::cout << "Connecting..." << std::endl;
    }

    std::cout << "Connected." << std::endl;

    while(true)
    {
        while(connection->hasMessages())
        {
            Message message;
            message = connection->nextMessage();

            QJsonDocument doc;
            doc.setObject(message.getData());

            std::cout << doc.toJson().data() << std::endl;
        }
    }
}
