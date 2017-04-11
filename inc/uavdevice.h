#ifndef UAVDEVICE_H
#define UAVDEVICE_H

#include <qstring.h>

class UAVDevice
{
public:
    UAVDevice();
    UAVDevice(uint8_t ID, uint8_t model, QString IP, int16_t port);

public:
    uint8_t ID;
    uint8_t model;
    QString IP;
    int16_t port;
};

#endif // UAVDEVICE_H
