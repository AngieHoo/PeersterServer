#include "serversocket.h"

ServerSocket::ServerSocket(QObject *parent) : QUdpSocket(parent){
    connect(this, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
}

bool ServerSocket::bind()
{
    if (QUdpSocket::bind(PORT)) {
        return true;
    }
    return false;
}

void ServerSocket::readPendingDatagrams() {
    while (hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(pendingDatagramSize());
        QHostAddress IP;
        quint16 Port;
        readDatagram(datagram.data(), datagram.size(),
                           &IP, &Port);
        emit processTheDatagram(datagram, IP, Port);
    }
    return;
}

void ServerSocket::sendMessage(const QHostAddress& sender, quint16 senderPort,const QVariantMap& message) {
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out << message;
    writeDatagram(data,sender, senderPort);
    return;
}
