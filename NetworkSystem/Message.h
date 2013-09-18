#ifndef MESSAGE_H
#define MESSAGE_H

#include <QHash>
#include <QQueue>
#include <QJsonObject>

class Message
{
    double m_type;

    qint64 m_sendTime;
    qint64 m_reciveTime;

    QJsonObject m_data;

public:
    enum TimeValue
    {
        TimeNotSet = -1
    };

    Message();
    ~Message();

    void setType(const double &par_type);
    double getType() const;

    void setSendTime(const qint64 &par_sendTime);
    qint64 getSendTime() const;

    void setData(const QJsonObject &par_data);
    QJsonObject getData() const;
};

#endif
