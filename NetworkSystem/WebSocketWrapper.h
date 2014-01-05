#ifndef WEBSOCKETWRAPPER_H
#define WEBSOCKETWRAPPER_H

#include <QObject>

#include <QTcpSocket>
#include "QWsSocket.h"

#include <QQueue>

class WebSocketWrapper: public QObject
{
    Q_OBJECT
private:
    QtWebsocket::QWsSocket *m_webSocket;

public:
    WebSocketWrapper();
    ~WebSocketWrapper();

    Q_INVOKABLE void initialize();
    Q_INVOKABLE void initialize(QtWebsocket::QWsSocket *par_wsSocket);
    Q_INVOKABLE void deinitialize();

    Q_INVOKABLE void connectToHost(const QString &par_address, const quint16 &par_port);
    Q_INVOKABLE QAbstractSocket::SocketState state();

    Q_INVOKABLE void write(const QString &par_data);

signals:
    void newMessageArrives(QString par_message);

private slots:
    void frameReceived(QString par_message);
    void frameReceived(QByteArray par_message);
};

#endif
