#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qstring.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->menuBar->setNativeMenuBar(false);

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
    connect(contactModel, SIGNAL(readyReadStandardOutput()),
            this, SLOT(on_newModelOutputGet()));

    modelViewDialog = new ModelViewDialog();
    deviceViewDialog = new DeviceViewDialog();

    sender = new QUdpSocket();
    stateNoModel();

    g_setting.clientPort = DEFAULT_CLIENT_PORT;
    listenerThread = new UDPThread();
    listenerThread->setPort(g_setting.clientPort);
    connect(listenerThread, SIGNAL(getMessage(QByteArray)),
            this, SLOT(on_controllerMessageReceived(QByteArray)));
    listenerThread->start();
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
void MainWindow::stateNoTask(void)
{
    g_status = TASK_STATUS::NO_TASK;

    ui->addDeviceButton->setEnabled(true);
    ui->taskButton->setEnabled(true);
    ui->startButton->setEnabled(false);
    ui->stopButton->setEnabled(false);

    ui->statusBar->showMessage("No task");
    consoleStr = TIME_STAMP + "No task";
    ui->console->append(consoleStr);
}

/**
 * @brief create UAV simulation model and communicate with the controller to valid the device
 * @param ID        new UAV ID
 * @param model     UAV model used in simulation
 * @param IP        controller IP address
 * @param port      controller process port
 */
void MainWindow::on_newDevAdded(uint8_t ID, uint8_t model, QString IP, uint16_t port)
{
    for (uint8_t i = 0; i < devices.length(); i++)
    {
        if (devices[i]->ID == ID)
        {
            consoleStr = TIME_STAMP + "Device [" + QString::number(ID) + "] already exists.";
            ui->console->append(consoleStr);
            return;
        }
    }

    devicesWaitForValid.append(new UAVDevice(ID, model, IP, port));
    sendValidNewDevice(ID, model, IP, port);

    consoleStr = TIME_STAMP + "Connecting controller at " + IP + ":" +
            QString::number(port);
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
 * @brief valid and create new model
 * @param nState        number of state
 * @param nControl      number of control
 * @param deltat        sample time Delta t
 * @param modelPath     path of model executable
 * @param modelName     model name
 */
void MainWindow::on_newModelAdded(uint8_t nState, uint8_t nControl, float deltat,
                                     QString modelPath, QString modelName)
{
    for (uint8_t i = 0; i < models.length(); i++)
    {
        if (models[i]->modelName == modelName)
        {
            consoleStr = TIME_STAMP + "Model [" + modelName + "] already exists.";
            ui->console->append(consoleStr);
            return;
        }
    }

    if (!validNewModel(nState, nControl, modelPath))
    {
        consoleStr = TIME_STAMP + "Wrong #state and/or #control.";
        ui->console->append(consoleStr);
    }
    else
    {
        consoleStr = TIME_STAMP + "Created new model [" + modelName + "]. Path = " + modelPath;
        ui->console->append(consoleStr);

        models.append(new UAVModel(nState, nControl, deltat, modelPath, modelName));
        addDeviceDialog->addNewModelToCombo(nState, nControl, modelName);
        modelViewDialog->addNewItem(modelName, deltat, nState, nControl);

        if (g_status == TASK_STATUS::NO_MODEL)
        {
            stateNoDevice();
        }
    }
}

/**
 * @brief read model output from std output
 */
void MainWindow::on_newModelOutputGet()
{
    QByteArray abc = contactModel->readAllStandardOutput();
    QString str = abc;
    ui->console->append(str);
}

/**
 * @brief create and send model validation data
 * @param nState        number of state
 * @param nControl      number of control
 * @param modelPath     path of model executable
 * @return  true when nState and nControl match the requirement of the executable
 */
bool MainWindow::validNewModel(uint8_t nState, uint8_t nControl, QString modelPath)
{
    QString proStr;

    proStr = modelPath + " ";
    for (uint8_t i = 0; i < nState + nControl + 1; i++)
    {
        proStr += (QString::number(0) + " ");
    }
    int result = contactModel->execute(proStr);

    if (result != 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

/**
 * @brief connect the controller at IP:port and check whether is available
 * @param ID        device ID
 * @param model     device model
 * @param IP        controller IP
 * @param port      controller process port
 */
void MainWindow::sendValidNewDevice(uint8_t ID, uint8_t model, QString IP, uint16_t port)
{
    QHostAddress controllerAddress = QHostAddress(IP);

    ClientToController message;
    message.type = MESSAGE_TYPE::CONNECTION;
    message.ID = ID;

    message.payLoad.connectionRequest.clientIP = static_cast<uint32_t>(QHostAddress(g_setting.clientIP).toIPv4Address());
    message.payLoad.connectionRequest.clientPort = g_setting.clientPort;
    message.payLoad.connectionRequest.model = model;
    message.payLoad.connectionRequest.nState = models[model]->nState;
    message.payLoad.connectionRequest.nControl = models[model]->nControl;
    sender->writeDatagram((char *)&message, sizeof(message), controllerAddress, port);
    qDebug() << sizeof(message);
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
                if (devicesWaitForValid.at(i)->ID == ID)
                {
                    const UAVDevice *temp = devicesWaitForValid.at(i);
                    devices.append(new UAVDevice(temp->ID,
                                                 temp->model,
                                                 temp->IP,
                                                 temp->port));
                    deviceViewDialog->addNewItem(temp->ID,
                                                 models[temp->model]->modelName,
                                                 temp->IP,
                                                 temp->port);
                    devicesWaitForValid.removeAt(i);
                    break;
                }
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
