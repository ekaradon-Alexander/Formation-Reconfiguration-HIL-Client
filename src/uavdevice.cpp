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

    this->contactModel = new QProcess();
//    connect(contactModel, SIGNAL(readyReadStandardOutput()),
//            this, SLOT(on_modelOutputGet()));
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

    this->contactModel = new QProcess();
//    connect(contactModel, SIGNAL(readyReadStandardOutput()),
//            this, SLOT(on_modelOutputGet()));
}

void UAVDevice::setStates(const float *states)
{
    for (uint8_t i = 0; i < modelPtr->nModelState; i++)
    {
        this->data->states[i] = states[i];
    }
}

void UAVDevice::getLocation(float &x, float &y, float &z)
{
    x = data->states[0];
    y = data->states[1];
    z = data->states[2];
}

void UAVDevice::establishShm(void)
{
    // setup shared memory in this process
    shmKey = 1000 + deviceID;
    int shmID;
    uint size = sizeof(Data);

    shmID = shmget(shmKey, size, 0666|IPC_CREAT);
    shm = shmat(shmID, 0, 0);
    data = (Data *)shm;

    // send message to set up shared memory in contactModel process
    QStringList params;
    params.append(QString::number(shmKey));
    qDebug() << QString("shm key = %1, addr = %2").arg((int)shmKey).arg((long)shm);
    data->shmCtl = 1;
    contactModel->start(modelPtr->modelPath, params);
}

void UAVDevice::destroyShm()
{
    simTimer->stop();
    usleep(15);
    data->shmCtl = 2;
    usleep(15);

    qDebug() << "ready to disattach shm";
    if (shmdt(shm) == -1)
    {
        qDebug() << "unable to disattach shm";
        contactModel->kill();
    }
}

void UAVDevice::requestUpdateStates(void)
{
    while (data->shmCtl == 0)
    {
        usleep(10);
    }
    // model: data->shmCtl = 1;
    data->controls[0] = 0.5;
    data->controls[1] = 0.01;
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
