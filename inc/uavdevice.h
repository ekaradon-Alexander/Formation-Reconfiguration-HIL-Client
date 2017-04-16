#ifndef UAVDEVICE_H
#define UAVDEVICE_H

#include <qstring.h>
#include <uavmodel.h>
#include <QTimer>
#include <QVector>
#include <QHostAddress>
#include <qcustomplot.h>
#include <QProcess>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>
#include <common.h>

typedef struct
{
    uint8_t shmCtl;
    float states[MAX_STATE_COUNT];
    float controls[MAX_CONTROL_COUNT];
} Data;

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

    key_t shmKey;
    void *shm;
    float *states;
    float *controls;
    QProcess *contactModel;

private:
    Data *data;

public:
    void setStates(const float *states);
    void getLocation(float &x, float &y, float &z);
    void requestUpdateStates(void);
    void establishShm(void);
    void destroyShm(void);

private slots:
    void on_timeOut(void);
    void on_modelOutputGet(void);
};

#endif // UAVDEVICE_H
