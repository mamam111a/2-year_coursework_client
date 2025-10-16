#ifndef SENDINFO_H
#define SENDINFO_H
#include <QTcpSocket>
#include <QString>

inline void sendToServer(QTcpSocket *socket, const QString &message)
{
    if(socket && socket->state() == QAbstractSocket::ConnectedState)
        socket->write(message.toUtf8());
}
#endif // SENDINFO_H
