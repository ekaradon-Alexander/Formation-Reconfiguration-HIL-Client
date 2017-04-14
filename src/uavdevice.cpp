#include "uavdevice.h"

UAVDevice::UAVDevice()
{

}

UAVDevice::UAVDevice(uint8_t ID, uint8_t model, QString IP, int16_t port)
{
    this->ID = ID;
    this->model = model;
    this->IP = IP;
    this->port = port;
    this->simTimer = new QTimer();
}
