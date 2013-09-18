#ifndef MESSAGESQUEUE_H
#define MESSAGESQUEUE_H

#include "Message.h"

#include <QHash>
#include <QQueue>

class MessagesQueue
{
    // Message type - message
    QHash<int, QQueue<Message>> m_messages;

public:
    MessagesQueue() {}
    ~MessagesQueue() {}

    void addMessage(const int &par_messageType, Message par_message);
    bool nextMessage(const int &par_messageType, Message * const par_message);
};

#endif
