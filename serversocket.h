#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H

#include <QUdpSocket>
#include <QVariantMap>
#include <QDebug>
#include <QDataStream>

#include "config.h"


class ServerSocket : public QUdpSocket
{
    Q_OBJECT
private slots:
    void readPendingDatagrams();

signals:
    void processTheDatagram(const QByteArray&, const QHostAddress& , const quint16&);

public:
    ServerSocket(QObject *parent = 0);
    void sendMessage(const QHostAddress& sender, quint16 senderPort,const QVariantMap& message);
    bool bind();

};
#endif // SERVERSOCKET_H
