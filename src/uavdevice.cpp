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

    states = new float[modelPtr->nModelState];
    controls = new float[modelPtr->nModelControl];
    for (uint8_t i = 0; i < modelPtr->nModelControl; i++)
    {
        this->controls[i] = 0.0;
    }

    this->contactModel = new QProcess();
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

    states = new float[modelPtr->nModelState];
    controls = new float[modelPtr->nModelControl];
    for (uint8_t i = 0; i < modelPtr->nModelControl; i++)
    {
        this->controls[i] = 0.0;
    }

    this->contactModel = new QProcess();
}

void UAVDevice::setStates(const float *states)
{
    for (uint8_t i = 0; i < modelPtr->nModelState; i++)
    {
        this->states[i] = states[i];
    }
}

void UAVDevice::getLocation(float *px, float *py, float *pz)
{
    *px = states[0];
    *py = states[1];
    *pz = states[2];
}

void UAVDevice::establishShm(void)
{
    // setup shared memory in this process
    shmKey = 2333 + deviceID;
    int shmID;
    uint size = sizeof(Data);

    shmID = shmget(shmKey, size, 0666|IPC_CREAT);
    shm = shmat(shmID, 0, 0);
    data = (Data *)shm;

    for (uint8_t i = 0; i < modelPtr->nModelState; i++)
    {
        data->states[i] = states[i];
    }
    for (uint8_t i = 0; i < modelPtr->nModelControl; i++)
    {
        data->controls[i] = controls[i];
    }

    // send message to set up shared memory in contactModel process
    QStringList params;
    params.append(QString::number(shmKey));
    data->shmCtl = 1;
    contactModel->start(modelPtr->modelPath, params);
}

void UAVDevice::destroyShm()
{
    simTimer->stop();
    usleep(15);
    contactModel->kill();
    shmdt(data);
}

void UAVDevice::requestUpdateStates(void)
{
    while (data->shmCtl == 0)
    {
        usleep(10);
    }
    // model: data->shmCtl = 1;
    // read states
    for (uint8_t i = 0; i < modelPtr->nModelState; i++)
    {
        states[i] = data->states[i];
    }
    // update controls
    for (uint8_t i = 0; i < modelPtr->nModelControl; i++)
    {
        data->controls[i] = controls[i];
    }
    data->shmCtl = 0;
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
