#ifndef USER_H
#define USER_H
#include <iostream>
#include <QString>
#include <QUdpSocket>
struct User
{
    QHostAddress addr;
    bool alive;
    User() {

    }
};

#endif // USER_H
