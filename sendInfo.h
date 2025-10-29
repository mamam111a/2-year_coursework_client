#ifndef SENDINFO_H
#define SENDINFO_H
#include <QTcpSocket>
#include <QString>
#include <arpa/inet.h>
inline void sendToServer(QTcpSocket *socket, const QString &message)
{
    if (!socket || socket->state() != QAbstractSocket::ConnectedState)
        return;
    QByteArray msgBytes = message.toUtf8();
    quint32 len = msgBytes.size();
    quint32 len_net = htonl(len);
    QByteArray packet;
    packet.append(reinterpret_cast<const char*>(&len_net), sizeof(len_net));
    packet.append(msgBytes);
    socket->write(packet);
}
#endif // SENDINFO_H
