#include "WebSocketWrapper.h"

#include <QDebug>

WebSocketWrapper::WebSocketWrapper(): QObject(0)
{
}

WebSocketWrapper::~WebSocketWrapper()
{
}

void WebSocketWrapper::initialize()
{
    m_webSocket = new QtWebsocket::QWsSocket();
    connect(m_webSocket, SIGNAL(frameReceived(QString)), this, SLOT(frameReceived(QString)));
    connect(m_webSocket, SIGNAL(frameReceived(QByteArray)), this, SLOT(frameReceived(QByteArray)));
}

void WebSocketWrapper::initialize(QtWebsocket::QWsSocket *par_wsSocket)
{
    m_webSocket = par_wsSocket;
    connect(m_webSocket, SIGNAL(frameReceived(QString)), this, SLOT(frameReceived(QString)));
    connect(m_webSocket, SIGNAL(frameReceived(QByteArray)), this, SLOT(frameReceived(QByteArray)));
}

void WebSocketWrapper::deinitialize()
{
    delete m_webSocket;
}

void WebSocketWrapper::connectToHost(const QString &par_address, const quint16 &par_port)
{
    QString address;
    address = "ws://" + par_address;
    m_webSocket->connectToHost(address, par_port);
}

QAbstractSocket::SocketState WebSocketWrapper::state()
{
    return m_webSocket->state();
}

void WebSocketWrapper::write(const QByteArray &par_data)
{
    qDebug()<<"Send:";
    qDebug()<<par_data;
    m_webSocket->write(par_data);
}

void WebSocketWrapper::frameReceived(QString par_message)
{
    qDebug()<<"Received:";
    qDebug()<<par_message;
    emit this->newMessageArrives(par_message);
}

void WebSocketWrapper::frameReceived(QByteArray par_message)
{
    qDebug()<<"Received:";
    qDebug()<<QString(par_message);
    emit this->newMessageArrives(QString(par_message));
}
