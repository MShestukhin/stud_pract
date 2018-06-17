#include "widget.h"
#include "ui_widget.h"
#include "QString"
#include "udpclient.h"
int count;
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{

    ui->setupUi(this);
    client=new UdpClient;
    connect(client->socket, SIGNAL(readyRead()), SLOT(read()));
    QString name="Полупокер";
    QString strName="EVMp_CONNECT_<"+QString::number(name.size())+">_<"+name+">";
    client->send("",strName);
    timer=new QTimer();
    timer->setInterval(3000);
    localUser=new User;
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
    timer->start();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    QString data="EVMp_SENDMSG_<"+QString::number(ui->lineEdit->text().size())+">_<"+ui->lineEdit->text()+">";
    client->send(ui->lineEdit_2->text(),data);
    ui->lineEdit->clear();
}

void Widget::read(){
    QString connect_str="CONNECT";
    QString alive_str="ALIVE";
    QString send_str="SENDMSG";
    QString str;
    QHostAddress sender;
    quint16 senderPort;
    while (client->socket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(client->socket->pendingDatagramSize());
        client->socket->readDatagram(datagram.data(), datagram.size(),&sender,&senderPort);
        str=datagram.data();
    }
    QString read_data=str;
    User user;
    user.addr=sender;
    user.alive=true;
    if(read_data.contains(connect_str)){
        client->map->insert(read_data.mid(read_data.indexOf(">_<")+3,(read_data.size()-read_data.indexOf(">_<")-4)),user);
    }
    if(read_data.contains(alive_str)){
        QString alive_msg=read_data.mid(read_data.indexOf(">_<")+3,(read_data.size()-read_data.indexOf(">_<")-4));
        client->map->find(alive_msg).value()=user;
    }
    if(read_data.contains(send_str)){
        ui->textEdit->append(read_data.mid(read_data.indexOf(">_<")+2));
    }
}

void Widget::updateTime(){
    count++;
    QString name="Полупокер";
    QString strName="EVMp_ALIVE_<"+QString::number(name.size())+">_<"+name+">";
    client->send("",strName);
    if(count>=2){
        ui->textEdit_2->clear();
        QMap<QString, User>::const_iterator i = client->map->constBegin();
        while (i != client->map->constEnd()) {
           if(i.value().alive){
                ui->textEdit_2->append(i.key());
            }
           client->map->find(i.key()).value().alive=false;
            ++i;
        }
        count=0;
    }
}
