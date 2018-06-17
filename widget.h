#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTime>
#include <QTimer>
#include "udpclient.h"
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_clicked();
    void read();
    void updateTime();

private:
    User* localUser;
    Ui::Widget *ui;
    UdpClient* client;
    QTimer *timer;
};

#endif // WIDGET_H
