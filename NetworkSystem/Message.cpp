#include "Message.h"

#include <QJsonDocument>
#include <QDebug>

Message::Message()
{
    m_type = -1;

    m_sendTime = Message::TimeNotSet;
}

Message::~Message()
{

}

void Message::setType(const double &par_type)
{
    m_type = par_type;
}

double Message::getType() const
{
    return m_type;
}

void Message::setSendTime(const qint64 &par_sendTime)
{
    m_sendTime = par_sendTime;
}

qint64 Message::getSendTime() const
{
    return m_sendTime;
}

void Message::setData(const QJsonObject &par_data)
{
    m_data = par_data;
}

QJsonObject Message::getData() const
{
    return m_data;
}
