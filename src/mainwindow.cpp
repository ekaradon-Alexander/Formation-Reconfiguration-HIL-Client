#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qstring.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->menuBar->setNativeMenuBar(false);
    ui->map->setEnabled(false);

    addModelDialog = new AddModelDialog(this);
    connect(addModelDialog, SIGNAL(sendNewModelData(uint8_t, uint8_t, float, QString, QString)),
            this, SLOT(on_newModelAdded(uint8_t, uint8_t, float, QString, QString)));

    addDeviceDialog = new AddDeviceDialog(this);
    connect(addDeviceDialog, SIGNAL(sendNewDevData(uint8_t, uint8_t, QString, uint16_t)),
            this, SLOT(on_newDevAdded(uint8_t, uint8_t, QString, uint16_t)));

    settingDialog = new SettingDialog(this);
    connect(settingDialog, SIGNAL(sendSettingData(uint16_t, QString)),
            this, SLOT(on_newSettingReceived(uint16_t, QString)));

    contactModel = new QProcess();

    modelViewDialog = new ModelViewDialog();
    deviceViewDialog = new DeviceViewDialog();

    missionDialog = new MissionDialog();
    connect(missionDialog, SIGNAL(sendNewMissionData(QVector<uint8_t>, QVector<QString>, QVector<uint8_t>, QVector<QString>)),
            this, SLOT(on_newMissionReceived(QVector<uint8_t>, QVector<QString>, QVector<uint8_t>, QVector<QString>)));

    sender = new QUdpSocket();
    stateNoModel();

    mission = new Mission();

    listenerThread = new UDPThread();
    listenerThread->setPort(g_setting.clientPort);
    connect(listenerThread, SIGNAL(getMessage(QByteArray)),
            this, SLOT(on_controllerMessageReceived(QByteArray)));
    listenerThread->start();

    plotTimer = new QTimer();
    plotTimer->setInterval(500);
    connect(plotTimer, SIGNAL(timeout()), this, SLOT(updateMap()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief change system status to NO_MODEL
 */
void MainWindow::stateNoModel(void)
{
    g_status = TASK_STATUS::NO_MODEL;

    ui->addDeviceButton->setEnabled(false);
    ui->taskButton->setEnabled(false);
    ui->startButton->setEnabled(false);
    ui->stopButton->setEnabled(false);

    ui->statusBar->showMessage("No model");
    consoleStr = TIME_STAMP + "No model";
    ui->console->append(consoleStr);
}

/**
 * @brief change system status to NO_DEVICE
 */
void MainWindow::stateNoDevice(void)
{
    g_status = TASK_STATUS::NO_DEVICE;

    ui->addDeviceButton->setEnabled(true);
    ui->taskButton->setEnabled(false);
    ui->startButton->setEnabled(false);
    ui->stopButton->setEnabled(false);

    ui->statusBar->showMessage("No device");
    consoleStr = TIME_STAMP + "No device";
    ui->console->append(consoleStr);
}

/**
 * @brief change system status to NO_TASK
 */
void MainWindow::stateNoMission(void)
{
    g_status = TASK_STATUS::NO_MISSION;

    ui->addDeviceButton->setEnabled(true);
    ui->taskButton->setEnabled(true);
    ui->startButton->setEnabled(false);
    ui->stopButton->setEnabled(false);

    ui->statusBar->showMessage("No task");
    consoleStr = TIME_STAMP + "No task";
    ui->console->append(consoleStr);
}

/**
 * @brief change system status to READY
 */
void MainWindow::stateReady()
{
    g_status = TASK_STATUS::READY;

    ui->addDeviceButton->setEnabled(true);
    ui->taskButton->setEnabled(true);
    ui->startButton->setEnabled(true);
    ui->stopButton->setEnabled(false);

    ui->statusBar->showMessage("Ready");
    consoleStr = TIME_STAMP + "Ready";
    ui->console->append(consoleStr);

    initMap();
}

void MainWindow::stateSimulation(void)
{
    g_status == TASK_STATUS::SIMULATION;

    ui->addDeviceButton->setEnabled(false);
    ui->taskButton->setEnabled(false);
    ui->startButton->setEnabled(false);
    ui->stopButton->setEnabled(true);

    ui->statusBar->showMessage("Simulation running");
    consoleStr = TIME_STAMP + "Simulation running";
    ui->console->append(consoleStr);
}

/**
 * @brief create UAV simulation model and communicate with the controller to valid the device
 * @param ID        new UAV ID
 * @param model     UAV model used in simulation
 * @param IP        controller IP address
 * @param port      controller process port
 */
void MainWindow::on_newDevAdded(uint8_t deviceID, uint8_t modelID,
                                QString controllerIP, uint16_t controllerPort)
{
    // check if device ID already exist
    for (uint8_t i = 0; i < devices.length(); i++)
    {
        if (devices.at(i)->deviceID == deviceID)
        {
            consoleStr = TIME_STAMP + "Device [" + QString::number(deviceID) + "] already exists.";
            ui->console->append(consoleStr);
            return;
        }
    }

    // send valid msg to controller
    devicesWaitForValid.append(new UAVDevice(deviceID, modelID, models,
                                             controllerIP, controllerPort));
    sendValidNewDevice(devicesWaitForValid.last());

    consoleStr = TIME_STAMP + "Connecting controller at " + controllerIP + ":" +
            QString::number(controllerPort);
    ui->console->append(consoleStr);
}

/**
 * @brief change global setting structure when receiving new setting data
 * @param clientPort    client port in setting window
 * @param clientIP      client IP in setting window
 */
void MainWindow::on_newSettingReceived(uint16_t clientPort, QString clientIP)
{
    g_setting.clientPort = clientPort;
    g_setting.clientIP = clientIP;
}

/**
 * @brief valid new mission item and add it to mission
 * @param initialID
 * @param initialData
 * @param targetID
 * @param targetData
 */
void MainWindow::on_newMissionReceived(QVector<uint8_t> initialID, QVector<QString> initialData,
                                       QVector<uint8_t> targetID, QVector<QString> targetData)
{
    for (uint8_t i = 0; i < initialID.length(); i++)
    {
        uint8_t model, nState, deviceID = initialID.at(i);

        // check device information
        for (uint8_t j = 0; j < devices.length(); j++)
        {
            if (devices.at(j)->deviceID == deviceID)
            {
                model = devices.at(j)->modelID;
                nState = devices.at(j)->modelPtr->nModelState;
            }
        }

        // split initialData
        QStringList initialDataList = initialData.at(i).split(',');
        QVector<float> initState;
        if (initialDataList.length() != nState)
        {
            QMessageBox::critical(0, "ERROR", QString("Device %1 has %2 states.").arg(deviceID).arg(nState),
                                  QMessageBox::Ok);
            return;
        }
        else
        {
            for (uint8_t j = 0; j < initialDataList.length(); j++)
            {
                initState.append(initialDataList.at(j).toFloat());
            }
        }

        // split targetData
        QStringList targetDataList;
        QVector<float> targetState;
        for (uint8_t j = 0; j < targetID.length(); j++)
        {
            if (targetID.at(j) == deviceID)
            {
                targetDataList = targetData.at(j).split(',');
                if (targetDataList.length() < 3)
                {
                    QMessageBox::critical(0, "ERROR",
                                          QString("Device %1 needs at least location information (x, y, h) as target state.").arg(deviceID));
                    return;
                }
                else
                {
                    for (uint8_t k = 0; k < targetDataList.length(); k++)
                    {
                        targetState.append(targetDataList.at(k).toFloat());
                    }
                }
            }
        }

        // add new mission item
        qDebug() << initState.length() << targetState.length();
        mission->updateMissionItem(deviceID, initState, targetState);
    }

    mission->dispMissionItem();
    stateReady();
}

/**
 * @brief valid and create new model
 * @param nState        number of state
 * @param nControl      number of control
 * @param deltat        sample time Delta t
 * @param modelPath     path of model executable
 * @param modelName     model name
 */
void MainWindow::on_newModelAdded(uint8_t nModelState, uint8_t nModelControl, float deltat,
                                  QString modelPath, QString modelName)
{
    // check if modelName already exist
    for (uint8_t i = 0; i < models.length(); i++)
    {
        if (models.at(i)->modelName == modelName)
        {
            consoleStr = TIME_STAMP + "Model [" + modelName + "] already exists.";
            ui->console->append(consoleStr);
            return;
        }
    }

    // valid nState and nControl
    if (!validNewModel(nModelState, nModelControl, modelPath))
    {
        consoleStr = TIME_STAMP + "Wrong #state and/or #control.";
        ui->console->append(consoleStr);
    }
    else
    {
        consoleStr = TIME_STAMP + "Created new model [" + modelName + "]. Path = " + modelPath;
        ui->console->append(consoleStr);

        models.append(new UAVModel(nModelState, nModelControl, deltat, modelPath, modelName));
        addDeviceDialog->addNewModelToCombo(nModelState, nModelControl, modelName);
        modelViewDialog->addNewItem(modelName, deltat, nModelState, nModelControl);

        if (g_status == TASK_STATUS::NO_MODEL)
        {
            stateNoDevice();
        }
    }
}

/**
 * @brief create and send model validation data
 * @param nState        number of state
 * @param nControl      number of control
 * @param modelPath     path of model executable
 * @return  true when nState and nControl match the requirement of the executable
 */
bool MainWindow::validNewModel(uint8_t nModelState, uint8_t nModelControl, QString modelPath)
{
    QString proStr;

    proStr = modelPath + " ";
    for (uint8_t i = 0; i < nModelState + nModelControl + 1; i++)
    {
        proStr += (QString::number(0) + " ");
    }
    int result = contactModel->execute(proStr);

    if (result != 1)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void MainWindow::sendValidNewDevice(UAVDevice *device)
{
    QHostAddress controllerAddress = QHostAddress(device->controllerIP);
    ClientToController msg;

    msg.type = MESSAGE_TYPE::CONNECTION;
    msg.ID = device->deviceID;

    msg.payLoad.connectionRequest.clientIP = static_cast<uint32_t>(QHostAddress(g_setting.clientIP).toIPv4Address());
    msg.payLoad.connectionRequest.clientPort = g_setting.clientPort;
    msg.payLoad.connectionRequest.modelID = device->modelID;
    msg.payLoad.connectionRequest.nModelState = device->modelPtr->nModelState;
    msg.payLoad.connectionRequest.nModelControl = device->modelPtr->nModelControl;
    sender->writeDatagram((char *)&msg, sizeof(msg), controllerAddress, device->controllerPort);
}

void MainWindow::initMap(void)
{
    ui->map->setEnabled(true);
    ui->map->xAxis->setLabel("x [m]");
    ui->map->yAxis->setLabel("y [m]");

    // add mission initial locations
    ui->map->addGraph();
    for (uint8_t i = 0; i < devices.length(); i++)
    {
        ui->map->graph(0)->addData(mission->initial.at(i)->location[0],
                mission->initial.at(i)->location[1]);
    }
    ui->map->graph(0)->setAntialiased(true);
    ui->map->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->map->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 10));

    // add mission target locations
    ui->map->addGraph();
    for (uint8_t i = 0; i < devices.length(); i++)
    {
        ui->map->graph(1)->addData(mission->target.at(i)->location[0],
                mission->target.at(i)->location[1]);
    }
    ui->map->graph(1)->setAntialiased(true);
    ui->map->graph(1)->setLineStyle(QCPGraph::lsNone);
    ui->map->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 10));

    ui->map->rescaleAxes(true);
    ui->map->xAxis->scaleRange(1.1, ui->map->xAxis->range().center());
    ui->map->yAxis->scaleRange(1.1, ui->map->yAxis->range().center());
    ui->map->replot();
}

void MainWindow::updateMap()
{
    //qDebug() << "update map";
    ui->map->addGraph();
    ui->map->graph()->setLineStyle(QCPGraph::lsNone);
    ui->map->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 3));

    float x, y, z;
    for (uint8_t i = 0; i < devices.length(); i++)
    {
        devices.at(i)->getLocation(x, y, z);
        ui->map->graph()->addData(x, y);
        // qDebug() << QString("%1, %2").arg(x).arg(y);
    }
    ui->map->rescaleAxes(true);
    ui->map->xAxis->scaleRange(1.1, ui->map->xAxis->range().center());
    ui->map->yAxis->scaleRange(1.1, ui->map->yAxis->range().center());
    ui->map->replot();
}

/**
 * @brief process message from controller according to protocol in controllercommunication.h
 * @param msg       message from controller
 */
void MainWindow::on_controllerMessageReceived(QByteArray msg)
{
    char *data = msg.data();
    ControllerToClient *mmsg = (ControllerToClient *)(data);
    uint8_t ID = mmsg->ID;
    switch (mmsg->type)
    {
    case CONNECTION:
    {
        for (int i = 0; i < devicesWaitForValid.length(); i++)
        {
            if (devicesWaitForValid.at(i)->deviceID == ID)
            {
                UAVDevice *temp = devicesWaitForValid.at(i);
                devices.append(new UAVDevice(*temp));
                deviceViewDialog->addNewItem(temp->deviceID,
                                             temp->modelPtr->modelName,
                                             temp->controllerIP.toString(),
                                             temp->controllerPort);
                missionDialog->addNewItem(temp->deviceID, temp->modelPtr->modelName);
                devicesWaitForValid.removeAt(i);
                consoleStr = TIME_STAMP + QString("Connected to device [%1].").arg(temp->deviceID);
                ui->console->append(consoleStr);
                break;
            }
        }

        if (g_status == TASK_STATUS::NO_DEVICE)
        {
            stateNoMission();
        }
    }; break;
    }
}


void MainWindow::on_addDeviceButton_clicked()
{
    addDeviceDialog->exec();
}

void MainWindow::on_addModelButton_clicked()
{
    addModelDialog->exec();
}

void MainWindow::on_actionShow_All_Models_triggered()
{
    modelViewDialog->exec();
}

void MainWindow::on_actionSet_triggered()
{
    settingDialog->refreshIPAddress();
    settingDialog->exec();
}

void MainWindow::on_actionShow_All_Devices_triggered()
{
    deviceViewDialog->exec();
}

void MainWindow::on_taskButton_clicked()
{
    missionDialog->exec();
}

void MainWindow::on_startButton_clicked()
{
    for (uint8_t i = 0; i < devices.length(); i++)
    {
        devices.at(i)->establishShm();
    }
    qDebug() << "shared memory set";
    for (uint8_t i = 0; i < devices.length(); i++)
    {
        devices.at(i)->setStates(mission->initial.at(i)->location);
    }
    qDebug() << "init state set";
    for (uint8_t i = 0; i < devices.length(); i++)
    {
        devices.at(i)->simTimer->start();
    }
    qDebug() << "simTimer start";
    plotTimer->start();

    stateSimulation();
}

void MainWindow::on_stopButton_clicked()
{
//    for (uint8_t i = 0; i < devices.length(); i++)
//    {
//        devices.at(i)->simTimer->stop();
//    }
    for (uint8_t i = 0; i < devices.length(); i++)
    {
        devices.at(i)->destroyShm();
    }
}
