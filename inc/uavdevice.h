#ifndef UAVDEVICE_H
#define UAVDEVICE_H

#include <qstring.h>
#include <uavmodel.h>
#include <QTimer>
#include <QVector>
#include <QHostAddress>
#include <qcustomplot.h>
#include <QProcess>

class UAVDevice : public QObject
{
    Q_OBJECT

public:
    UAVDevice(uint8_t deviceID,
              uint8_t modelID, const QVector<UAVModel *> &modelList,
              QString controllerIPStr, int16_t controllerPort);
    UAVDevice(const UAVDevice &old);

public:
    uint8_t deviceID;
    uint8_t modelID;
    const UAVModel *modelPtr;
    QHostAddress controllerIP;
    int16_t controllerPort;
    QTimer *simTimer;
    float *states;
    float *controls;
    QProcess *contactModel;

public:
    void setStates(const float *states);
    void getLocation(float &x, float &y, float &z);
    void requestUpdateStates(void);

private slots:
    void on_timeOut(void);
    void on_modelOutputGet(void);
};

#endif // UAVDEVICE_H
