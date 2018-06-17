#include "udpclient.h"
#include <QDebug>
UdpClient::UdpClient()
{
    //QMap<QString, bool> map;
    map=new QMap<QString, User>;
    socket = new QUdpSocket;
    socket->bind(QHostAddress::Any, 14000);
}
QString UdpClient::read(){
    QString str;
    QHostAddress sender;
    quint16 senderPort;
    while (socket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(socket->pendingDatagramSize());
        socket->readDatagram(datagram.data(), datagram.size(),&sender,&senderPort);
   //     map->insert(arg(datagram.data()),true);
        /*statusLabel->setText(tr("Received datagram: \"%1\"")
                             .arg(datagram.data()));*/
        str=datagram.data();
    }
    return str;
}
void UdpClient::send(QString host,QString data){
    if(host.isEmpty())
        socket->writeDatagram(data.toStdString().c_str(), QHostAddress::Broadcast, 14000);
    else{
        socket->writeDatagram(data.toStdString().c_str(), map->find(host).value().addr, 14000);
    }
}
