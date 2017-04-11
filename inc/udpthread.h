#ifndef UDPTHREAD_H
#define UDPTHREAD_H

#include <qthread.h>
#include <qudpsocket.h>
#include <qbytearray.h>
#include <inttypes.h>

class UDPThread : public QThread
{
    Q_OBJECT

public:
    explicit UDPThread(QObject *parent = 0);
    ~UDPThread();

public:
    void setPort(uint16_t port);
    void run(void);

private:
    uint16_t port;
    QUdpSocket *receiver;

signals:
    void getMessage(QByteArray msg);

private slots:
    void on_dataReceived(void);

};

#endif // UDPTHREAD_H
