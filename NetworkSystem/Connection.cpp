#include "Connection.h"

#include <QMetaObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>

Connection::Connection(QThread *par_connectionsThread, QObject *par_parent): QObject(par_parent)
{
    m_webSocketWrapper = new WebSocketWrapper();
    m_webSocketWrapper->moveToThread(par_connectionsThread);
    QObject::connect(m_webSocketWrapper,
                     SIGNAL(newMessageArrives(QString)),
                     this,
                     SLOT(on_newMessageArrives(QString)));

    QMetaObject::invokeMethod(m_webSocketWrapper,
                              "initialize",
                              Qt::BlockingQueuedConnection);
}

Connection::Connection(QThread *par_connectionsThread, QtWebsocket::QWsSocket *par_wsSocket, QObject *par_parent): QObject(par_parent)
{
    m_webSocketWrapper = new WebSocketWrapper();
    m_webSocketWrapper->moveToThread(par_connectionsThread);
    QObject::connect(m_webSocketWrapper,
                     SIGNAL(newMessageArrives(QString)),
                     this,
                     SLOT(on_newMessageArrives(QString)));

    par_wsSocket->moveToThread(par_connectionsThread);

    QMetaObject::invokeMethod(m_webSocketWrapper,
                              "initialize",
                              Qt::BlockingQueuedConnection,
                              Q_ARG(QtWebsocket::QWsSocket*, par_wsSocket));
}

Connection::~Connection()
{
    QMetaObject::invokeMethod(m_webSocketWrapper,
                              "deinitialize",
                              Qt::BlockingQueuedConnection);
    delete m_webSocketWrapper;
}

void Connection::connectToHost(const QString &par_address, const quint16 &par_port)
{
    QMetaObject::invokeMethod(m_webSocketWrapper,
                              "connectToHost",
                              Qt::BlockingQueuedConnection,
                              Q_ARG(QString, par_address),
                              Q_ARG(quint16, par_port));
}

QAbstractSocket::SocketState Connection::state()
{
    QAbstractSocket::SocketState state;

    QMetaObject::invokeMethod(m_webSocketWrapper,
                              "state",
                              Qt::BlockingQueuedConnection,
                              Q_RETURN_ARG(QAbstractSocket::SocketState, state));

    return state;
}

void Connection::addMessage(const Message &par_message)
{
    m_toSendMessages.enqueue(par_message);
}

bool Connection::hasMessages()
{
    return !m_receivedMessages.empty();
}

Message Connection::nextMessage()
{
    return m_receivedMessages.dequeue();
}

void Connection::sendMessages()
{
    QJsonArray messages;

    while(!m_toSendMessages.empty())
    {
        Message message;
        message = m_toSendMessages.dequeue();

        QJsonObject messageObject;
        messageObject.insert("message_type", message.getType());
        messageObject.insert("message_time", QString::number(message.getSendTime()));
        messageObject.insert("data", message.getData());

        messages.append(messageObject);
    }

    QJsonDocument doc;
    doc.setArray(messages);

    QMetaObject::invokeMethod(m_webSocketWrapper,
                              "write",
                              Qt::BlockingQueuedConnection,
                              Q_ARG(const QString&, doc.toJson(QJsonDocument::Compact)));
}

void Connection::on_newMessageArrives(QString par_message)
{
    QJsonDocument doc;
    doc = QJsonDocument::fromJson(par_message.toUtf8());

    QJsonArray messages;
    messages = doc.array();

    QJsonArray::Iterator messagesIter;
    messagesIter = messages.begin();
    while(messagesIter != messages.end())
    {
        QJsonObject messageObject;
        messageObject = (*messagesIter).toObject();

        Message message;
        message.setType(messageObject.value("message_type").toDouble());
        message.setSendTime(messageObject.value("message_time").toString().toLongLong());
        message.setData(messageObject.value("data").toObject());

        m_receivedMessages.enqueue(message);

        ++messagesIter;
    }
}
