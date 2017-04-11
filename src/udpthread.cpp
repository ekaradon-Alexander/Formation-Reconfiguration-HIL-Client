#include "udpthread.h"

UDPThread::UDPThread(QObject *parent) :
    QThread(parent)
{

}

UDPThread::~UDPThread()
{
    receiver->deleteLater();
    quit();
    wait();
}

void UDPThread::run(void)
{
    receiver = new QUdpSocket();
    receiver->bind(port, QUdpSocket::ShareAddress);
    connect(receiver, SIGNAL(readyRead()),
            this, SLOT(on_dataReceived()), Qt::DirectConnection);
    exec();
}

void UDPThread::setPort(uint16_t port)
{
    this->port = port;
}

void UDPThread::on_dataReceived(void)
{
    while (receiver->hasPendingDatagrams())
    {
        QByteArray datagram;

        datagram.resize(receiver->pendingDatagramSize());

        QHostAddress senderAddress;
        uint16_t senderPort;

        receiver->readDatagram(datagram.data(), datagram.size(),
                               &senderAddress, &senderPort);

        emit getMessage(datagram);
    }
}
