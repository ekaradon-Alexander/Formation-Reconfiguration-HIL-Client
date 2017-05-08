#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qstring.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->actionAdd_Model->setShortcut(QKeySequence("Ctrl+1"));
    ui->actionAdd_Device->setShortcut(QKeySequence("Ctrl+2"));
    ui->actionMission->setShortcut(QKeySequence("Ctrl+3"));
    ui->actionStart->setShortcut(QKeySequence("Ctrl+4"));
    ui->actionStop->setShortcut(QKeySequence("Ctrl+5"));

    ui->actionShow_All_Models->setShortcut(QKeySequence("Ctrl+Shift+M"));
    ui->actionShow_All_Devices->setShortcut(QKeySequence("Ctrl+Shift+D"));

    ui->actionSet->setShortcut(QKeySequence("Ctrl+,"));

    ui->menuBar->setNativeMenuBar(false);

    addModelDialog = new AddModelDialog(this);
    connect(addModelDialog, SIGNAL(sendNewModelData(uint8_t, uint8_t, float, QString, QString)),
            this, SLOT(on_newModelAdded(uint8_t, uint8_t, float, QString, QString)));

    addDeviceDialog = new AddDeviceDialog(this);
    connect(addDeviceDialog, SIGNAL(sendNewDevData(uint8_t, uint8_t, QString, uint16_t)),
            this, SLOT(on_newDevAdded(uint8_t, uint8_t, QString, uint16_t)));

    settingDialog = new SettingDialog(this);
    connect(settingDialog, SIGNAL(sendSettingData(uint16_t, QString, uint16_t, uint16_t)),
            this, SLOT(on_newSettingReceived(uint16_t, QString, uint16_t, uint16_t)));

    contactModel = new QProcess();

    modelViewDialog = new ModelViewDialog(this);
    deviceViewDialog = new DeviceViewDialog(this);
    connect(deviceViewDialog, SIGNAL(sendReconnectButton()),
            this, SLOT(on_reconnectMessageReceived()));

    missionDialog = new MissionDialog(this);
    connect(missionDialog, SIGNAL(sendNewMissionData(QVector<uint8_t>, QVector<QString>, QVector<uint8_t>, QVector<QString>)),
            this, SLOT(on_newMissionReceived(QVector<uint8_t>, QVector<QString>, QVector<uint8_t>, QVector<QString>)));

    sender = new QUdpSocket();
    mission = new Mission();

    listenerThread = new UDPThread();
    listenerThread->setPort(g_setting.clientPort);
    connect(listenerThread, SIGNAL(getMessage(QByteArray)),
            this, SLOT(on_controllerMessageReceived(QByteArray)));
    listenerThread->start();

    plotTimer = new QTimer();
    //    plotTimer->setInterval(100);
    connect(plotTimer, SIGNAL(timeout()), this, SLOT(on_plotTimerTimeout()));

    controlTimer = new QTimer();
    //    controlTimer->setInterval(500);
    connect(controlTimer, SIGNAL(timeout()), this, SLOT(on_controlTimerTimeout()));

    ui->height->xAxis->setVisible(false);
    stateNoModel();
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

    ui->actionAdd_Model->setEnabled(true);
    ui->actionAdd_Device->setEnabled(false);
    ui->actionMission->setEnabled(false);
    ui->actionStart->setEnabled(false);
    ui->actionStop->setEnabled(false);

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

    ui->actionAdd_Model->setEnabled(true);
    ui->actionAdd_Device->setEnabled(true);
    ui->actionMission->setEnabled(false);
    ui->actionStart->setEnabled(false);
    ui->actionStop->setEnabled(false);

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

    ui->actionAdd_Model->setEnabled(true);
    ui->actionAdd_Device->setEnabled(true);
    ui->actionMission->setEnabled(true);
    ui->actionStart->setEnabled(false);
    ui->actionStop->setEnabled(false);

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

    ui->actionAdd_Model->setEnabled(true);
    ui->actionAdd_Device->setEnabled(true);
    ui->actionMission->setEnabled(true);
    ui->actionStart->setEnabled(true);
    ui->actionStop->setEnabled(false);

    ui->statusBar->showMessage("Ready");
    consoleStr = TIME_STAMP + "Ready";
    ui->console->append(consoleStr);

    ui->actionStop->setText("Stop");
    initMap();
}

void MainWindow::stateSimulation(void)
{
    g_status = TASK_STATUS::SIMULATION;

    ui->actionAdd_Model->setEnabled(false);
    ui->actionAdd_Device->setEnabled(false);
    ui->actionMission->setEnabled(false);
    ui->actionStart->setEnabled(false);
    ui->actionStop->setEnabled(true);

    ui->statusBar->showMessage("Simulation running");
    consoleStr = TIME_STAMP + "Simulation running";
    ui->console->append(consoleStr);
}

void MainWindow::stateStop(void)
{
    g_status = TASK_STATUS::STOP;

    ui->actionAdd_Model->setEnabled(true);
    ui->actionAdd_Device->setEnabled(true);
    ui->actionMission->setEnabled(true);
    ui->actionStart->setEnabled(true);
    ui->actionStop->setEnabled(true);

    ui->actionStop->setText("Reset");
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
void MainWindow::on_newSettingReceived(uint16_t clientPort, QString clientIP,
                                       uint16_t plottingTime, uint16_t controlTime)
{
    g_setting.clientPort = clientPort;
    g_setting.clientIP = clientIP;
    g_setting.plottingTime = plottingTime;
    g_setting.controlTime = controlTime;
}

/**
 * @brief  new mission item and add it to mission
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
        mission->updateMissionItem(deviceID, initState, targetState);
    }

    uploadMission();
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
    // on map: add initial position
    ui->map->xAxis->setLabel("x [m]");
    ui->map->yAxis->setLabel("y [m]");

    for (uint8_t i = 0; i < devices.length(); i++)
    {
        colorList.append(QColor(
                             200.0 * (float)(rand()) / RAND_MAX,
                             200.0 * (float)(rand()) / RAND_MAX,
                             200.0 * (float)(rand()) / RAND_MAX));
    }

    for (uint8_t i = 0; i < devices.length(); i++)  // graphs 0 ~ (length-1): identify current location
    {
        ui->map->addGraph();
        QPen pen;
        pen.setColor(colorList.at(i));

        ui->map->graph(i)->setPen(pen);
        ui->map->graph(i)->addData(mission->initial.at(i)->location[0],
                mission->initial.at(i)->location[1]);
        ui->map->graph(i)->setLineStyle(QCPGraph::lsNone);
        ui->map->graph(i)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 1));
    }

    for (uint8_t i = devices.length(); i < 2 * devices.length(); i++)
    {
        ui->map->addGraph();
        QPen pen;
        pen.setColor(colorList.at(i - devices.length()));

        ui->map->graph(i)->setPen(pen);
        ui->map->graph(i)->addData(mission->initial.at(i - devices.length())->location[0],
                mission->initial.at(i - devices.length())->location[1]);
        ui->map->graph(i)->setLineStyle(QCPGraph::lsNone);
        ui->map->graph(i)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 7));
    }

    ui->map->rescaleAxes(true);
    ui->map->xAxis->scaleRange(1.1, ui->map->xAxis->range().center());
    ui->map->yAxis->scaleRange(1.1, ui->map->yAxis->range().center());
    ui->map->replot();

    // on minimap: add target relative position
    ui->minimap->xAxis->setLabel("relative x [m]");
    ui->minimap->yAxis->setLabel("relative y [m]");

    minimapXdata.resize(devices.length());
    minimapYdata.resize(devices.length());
    for (uint8_t i = 0; i < devices.length(); i++)
    {
        minimapXdata[i].resize(1);
        minimapYdata[i].resize(1);
        minimapXdata[i][0] = (mission->initial.at(i)->location[0] -
                mission->initial.at(0)->location[0]);
        minimapYdata[i][0] = (mission->initial.at(i)->location[1] -
                mission->initial.at(0)->location[1]);
    }

    for (uint8_t i = 0; i < devices.length(); i++)
    {
        ui->minimap->addGraph();
        QPen pen;
        pen.setColor(colorList.at(i));

        ui->minimap->graph(i)->setPen(pen);
        ui->minimap->graph(i)->setLineStyle(QCPGraph::lsNone);
        ui->minimap->graph(i)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 3));

        ui->minimap->graph(i)->setData(minimapXdata.at(i), minimapYdata.at(i));
    }

    for (uint8_t i = devices.length(); i < 2 * devices.length(); i++)
    {
        ui->minimap->addGraph();
        QPen pen;
        pen.setColor(colorList.at(i - devices.length()));

        ui->minimap->graph(i)->setPen(pen);
        ui->minimap->graph(i)->setLineStyle(QCPGraph::lsNone);
        ui->minimap->graph(i)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 4));

        ui->minimap->graph(i)->addData(mission->target.at(i - devices.length())->location[0],
                mission->target.at(i - devices.length())->location[1]);
    }

    ui->minimap->rescaleAxes(true);
    ui->minimap->xAxis->scaleRange(1.1, ui->minimap->xAxis->range().center());
    ui->minimap->yAxis->scaleRange(1.1, ui->minimap->yAxis->range().center());
    ui->minimap->replot();
}

void MainWindow::updateMap()
{
    float x, y, z;
    for (uint8_t i = 0; i < devices.length(); i++)
    {
        devices.at(i)->getLocation(&x, &y, &z);
        ui->map->graph(i)->addData(x, y);
        minimapXdata[i][0] = devices.at(i)->states[0] - devices.at(0)->states[0];
        minimapYdata[i][0] = devices.at(i)->states[1] - devices.at(0)->states[1];
        ui->minimap->graph(i)->setData(minimapXdata.at(i), minimapYdata.at(i));
    }

    ui->map->rescaleAxes(true);
    ui->map->xAxis->scaleRange(1.1, ui->map->xAxis->range().center());
    ui->map->yAxis->scaleRange(1.1, ui->map->yAxis->range().center());
    ui->map->replot();

    ui->minimap->rescaleAxes(true);
    ui->minimap->xAxis->scaleRange(1.1, ui->minimap->xAxis->range().center());
    ui->minimap->yAxis->scaleRange(1.1, ui->minimap->yAxis->range().center());
    ui->minimap->replot();
}

void MainWindow::uploadMission(void)
{
    QHostAddress controllerAddress;
    ClientToController msg;

    msg.type = MESSAGE_TYPE::MISSION;

    for (uint8_t i = 0; i < devices.length(); i++)
    {
        controllerAddress = QHostAddress(devices.at(i)->controllerIP);

        msg.ID = devices.at(i)->deviceID;
        msg.payLoad.targetInfo.nDevices = devices.length();

        for (uint8_t j = 0; j < mission->target.length(); j++)
        {
            if (msg.ID == mission->target.at(j)->ID)
            {
                msg.payLoad.targetInfo.nTargetState = mission->target.at(j)->length;
                for (uint8_t k = 0; k < mission->target.at(j)->length; k++)
                {
                    msg.payLoad.targetInfo.targetStates[k] = mission->target.at(j)->location[k];
                }
                break;
            }
        }

        sender->writeDatagram((char *)&msg, sizeof(msg), controllerAddress,
                              devices.at(i)->controllerPort);
    }
}

void MainWindow::broadcastStates(void)
{
    QHostAddress controllerAddress;
    ClientToController msg;

    msg.type = MESSAGE_TYPE::CONTROL;
    uint8_t centerIndex;

    for (uint8_t i = 0; i < devices.length(); i++)
    {
        if (devices.at(i)->deviceID == 1)
        {
            centerIndex = i;
        }
    }

    for (uint8_t i = 0; i < devices.length(); i++)
    {
        controllerAddress = QHostAddress(devices.at(i)->controllerIP);

        msg.ID = devices.at(i)->deviceID;

        msg.payLoad.controlRequest.nModelState = devices.at(i)->modelPtr->nModelState;
        for (uint8_t j = 0; j < msg.payLoad.controlRequest.nModelState; j++)
        {
            msg.payLoad.controlRequest.selfStates[j] = devices.at(i)->states[j];
            msg.payLoad.controlRequest.centerStates[j] = devices.at(centerIndex)->states[j];
        }

        sender->writeDatagram((char *)&msg, sizeof(msg), controllerAddress,
                              devices.at(i)->controllerPort);
    }
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
        if (mmsg->payLoad.connectionResult.valid == 0)
        {
            consoleStr = TIME_STAMP + QString("Controller [%1] refused connection.").arg(mmsg->ID);
            ui->console->append(consoleStr);
            break;
        }

        for (uint8_t i = 0; i < devices.length(); i++)
        {
            if (devices.at(i)->deviceID == ID)
            {
                UAVDevice *temp = devices.at(i);
                consoleStr = TIME_STAMP + QString("Reconnected to device [%1].").arg(temp->deviceID);
                ui->console->append(consoleStr);
                break;
            }
        }
        for (uint8_t i = 0; i < devicesWaitForValid.length(); i++)
        {
            if (devicesWaitForValid.at(i)->deviceID == ID)
            {
                UAVDevice *temp = devicesWaitForValid.at(i);
                devices.append(new UAVDevice(*temp));
                deviceViewDialog->addNewItem(temp->deviceID,
                                             temp->modelPtr->modelName,
                                             temp->controllerIP.toString(),
                                             temp->controllerPort);
                addDeviceDialog->incrementDeviceID(devices.length());
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
    case CONTROL:
    {
        for (int i = 0; i < devices.length(); i++)
        {
            if (devices.at(i)->deviceID == ID)
            {
                for (uint8_t j = 0; j < mmsg->payLoad.controlResult.nControllerControl; j++)
                {
                    devices.at(i)->controls[j] = mmsg->payLoad.controlResult.controls[j];
                }
            }
        }
    }; break;
    }
}

void MainWindow::on_reconnectMessageReceived()
{
    ClientToController msg;
    msg.type = MESSAGE_TYPE::CONNECTION;
    msg.payLoad.connectionRequest.clientIP = static_cast<uint32_t>(QHostAddress(g_setting.clientIP).toIPv4Address());
    msg.payLoad.connectionRequest.clientPort = g_setting.clientPort;

    foreach (UAVDevice *device, devices)
    {
        QHostAddress controllerAddress = QHostAddress(device->controllerIP);

        msg.ID = device->deviceID;
        msg.payLoad.connectionRequest.modelID = device->modelID;
        msg.payLoad.connectionRequest.nModelState = device->modelPtr->nModelState;
        msg.payLoad.connectionRequest.nModelControl = device->modelPtr->nModelControl;

        sender->writeDatagram((char *)&msg, sizeof(msg), controllerAddress, device->controllerPort);
    }
}

void MainWindow::on_plotTimerTimeout()
{
    updateMap();
}

void MainWindow::on_controlTimerTimeout()
{
    broadcastStates();
}

void MainWindow::on_actionShow_All_Models_triggered()
{
    modelViewDialog->show();
}

void MainWindow::on_actionSet_triggered()
{
    settingDialog->refreshIPAddress();
    settingDialog->exec();
}

void MainWindow::on_actionShow_All_Devices_triggered()
{
    deviceViewDialog->show();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::information(0, "About", QString("Bulid time: %1 %2").arg(__DATE__).arg(__TIME__),
                             QMessageBox::Ok);
}

void MainWindow::on_actionAdd_Model_triggered()
{
    addModelDialog->exec();
}

void MainWindow::on_actionAdd_Device_triggered()
{
    addDeviceDialog->exec();
}

void MainWindow::on_actionMission_triggered()
{
    missionDialog->exec();
}

void MainWindow::on_actionStart_triggered()
{
    for (uint8_t i = 0; i < devices.length(); i++)
    {
        devices.at(i)->setStates(mission->initial.at(i)->location);
    }

    for (uint8_t i = 0; i < devices.length(); i++)
    {
        devices.at(i)->establishShm();
    }

    for (uint8_t i = 0; i < devices.length(); i++)
    {
        devices.at(i)->simTimer->start();
    }

    plotTimer->setInterval(g_setting.plottingTime);
    plotTimer->start();

    controlTimer->setInterval(g_setting.controlTime);
    controlTimer->start();

    stateSimulation();
}

void MainWindow::on_actionStop_triggered()
{
    if (g_status == TASK_STATUS::SIMULATION)
    {
        for (uint8_t i = 0; i < devices.length(); i++)
        {
            devices.at(i)->destroyShm();
        }
        plotTimer->stop();
        controlTimer->stop();

        for (uint8_t i = 0; i < devices.length(); i++)
        {
            memset(devices.at(i)->controls, 0, sizeof(float) * MAX_CONTROL_COUNT);
        }

        stateStop();
    }
    else if (g_status == TASK_STATUS::STOP)
    {
        ui->map->clearGraphs();
        ui->minimap->clearGraphs();
        minimapXdata.clear();
        minimapYdata.clear();
        stateReady();
    }
}
