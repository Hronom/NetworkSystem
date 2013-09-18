#ifndef CONNECTION_H
#define CONNECTION_H

#include "WebSocketWrapper.h"
#include "Message.h"

#include <QObject>
#include <QQueue>

class Connection: public QObject
{
    Q_OBJECT
private:
    WebSocketWrapper *m_webSocketWrapper;

    // Message type - message data
    QQueue<Message> m_toSendMessages;

    // Message type - message data
    QQueue<Message> m_receivedMessages;

public:
    Connection(QThread *par_connectionsThread, QObject *par_parent = 0);
    Connection(QThread *par_connectionsThread, QtWebsocket::QWsSocket *par_wsSocket, QObject *par_parent = 0);
    ~Connection();

    void connectToHost(const QString &par_address, const quint16 &par_port);
    QAbstractSocket::SocketState state();

    void addMessage(const Message &par_message);
    bool hasMessages();
    Message nextMessage();
    void sendMessages();

private slots:
    void on_newMessageArrives(QString par_message);
};

#endif
