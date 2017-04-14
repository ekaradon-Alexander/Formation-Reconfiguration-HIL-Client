#include "uavdevice.h"

UAVDevice::UAVDevice(uint8_t deviceID,
                     uint8_t modelID, const QVector<UAVModel *> &modelList,
                     QString controllerIPStr, int16_t controllerPort)
{
    this->deviceID = deviceID;
    this->modelID = modelID;
    this->modelPtr = modelList.at(modelID);
    this->controllerIP = QHostAddress(controllerIPStr);
    this->controllerPort = controllerPort;

    this->simTimer = new QTimer();
    this->simTimer->setInterval(modelPtr->deltat * 1000);
    connect(simTimer, SIGNAL(timeout()), this, SLOT(on_timeOut()));

    this->states = new float[modelPtr->nModelState];
    this->controls = new float[modelPtr->nModelControl];

    this->contactModel = new QProcess();
    connect(contactModel, SIGNAL(readyReadStandardOutput()),
            this, SLOT(on_modelOutputGet()));

    this->controls[0] = 10;
    this->controls[1] = 20;
}

UAVDevice::UAVDevice(const UAVDevice &old)
{
    this->deviceID = old.deviceID;
    this->modelID = old.modelID;
    this->modelPtr = old.modelPtr;
    this->controllerIP = old.controllerIP;
    this->controllerPort = old.controllerPort;

    this->simTimer = new QTimer();
    this->simTimer->setInterval(modelPtr->deltat * 1000);
    connect(simTimer, SIGNAL(timeout()), this, SLOT(on_timeOut()));

    this->states = new float[modelPtr->nModelState];
    this->controls = new float[modelPtr->nModelControl];

    this->contactModel = new QProcess();
    connect(contactModel, SIGNAL(readyReadStandardOutput()),
            this, SLOT(on_modelOutputGet()));

    this->controls[0] = 10;
    this->controls[1] = 20;
}

void UAVDevice::setStates(const float *states)
{
    for (uint8_t i = 0; i < modelPtr->nModelState; i++)
    {
        this->states[i] = states[i];
    }
}

void UAVDevice::getLocation(float &x, float &y, float &z)
{
    x = states[0];
    y = states[1];
    z = states[2];
}

void UAVDevice::requestUpdateStates(void)
{
    QString proStr = modelPtr->modelPath + " " + QString::number(deviceID) + " ";

    for (uint8_t i = 0; i < modelPtr->nModelState; i++)
    {
        proStr += (QString::number(states[i]) + " ");
    }
    for (uint8_t i = 0; i < modelPtr->nModelControl; i++)
    {
        proStr += (QString::number(controls[i]) + " ");
    }

    qDebug() << proStr;
    contactModel->start(proStr);
}

void UAVDevice::on_timeOut(void)
{
    requestUpdateStates();
}

void UAVDevice::on_modelOutputGet()
{
    QByteArray resultStreamData = contactModel->readAllStandardOutput();
    QList<QByteArray> resultList = resultStreamData.split(' ');

    float *stateResults = new float[resultList.length() - 1];
    for (uint8_t i = 0; i < resultList.length() - 1; i++)
    {
        stateResults[i] = resultList.at(i + 1).toFloat();
    }

    setStates(stateResults);
}
