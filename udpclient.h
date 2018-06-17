#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <QObject>
#include <QUdpSocket>
#include <QMap>
#include <QStringList>
#include "user.h"
class UdpClient : public QObject
{
public:
    UdpClient();
    QUdpSocket* socket;
    QString read();
    void send(QString host, QString data);
    QMap<QString, User>* map;
    QStringList* list;
};

#endif // UDPCLIENT_H
