#include "MessagesQueue.h"

#include <QDebug>

void MessagesQueue::addMessage(const int &par_messageType, Message par_message)
{
    m_messages[par_messageType].enqueue(par_message);
}

bool MessagesQueue::nextMessage(const int &par_messageType, Message * const par_message)
{
    if(!m_messages[par_messageType].empty())
    {
        (*par_message) = m_messages[par_messageType].dequeue();
        return true;
    }
    else
    {
        return false;
    }
}
