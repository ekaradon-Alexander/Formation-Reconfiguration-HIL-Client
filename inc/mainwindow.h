#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qdatetime.h>
#include <qstring.h>
#include <qtimer.h>
#include <qthread.h>

#include <adddevicedialog.h>
#include <addmodeldialog.h>
#include <modelviewdialog.h>
#include <settingdialog.h>
#include <deviceviewdialog.h>

#include <QtNetwork>
#include <qvector.h>
#include <uavmodel.h>
#include <uavdevice.h>
#include <qprocess.h>
#include <QDebug>
#include <controllercommunication.h>

#include <common.h>
#include <udpthread.h>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString consoleStr;
    QTimer simTimer;

    AddDeviceDialog *addDeviceDialog;
    AddModelDialog *addModelDialog;
    ModelViewDialog *modelViewDialog;
    DeviceViewDialog *deviceViewDialog;
    SettingDialog *settingDialog;

    QUdpSocket *sender;
    uint16_t receivePort;

    QVector<UAVModel *> models;
    QVector<UAVDevice *> devices;
    QVector<UAVDevice *> devicesWaitForValid;

    QProcess *contactModel;
    QProcess *listenController;

    UDPThread *listenerThread;

private:
    void stateNoModel(void);
    void stateNoDevice(void);
    void stateNoTask(void);

private:
    bool validNewModel(uint8_t nState, uint8_t nControl, QString modelPath);
    void sendValidNewDevice(uint8_t ID, uint8_t model, QString IP, uint16_t port);

private slots:
    void on_newModelAdded(uint8_t nState, uint8_t nControl, float deltat,
                             QString modelPath, QString modelName);
    void on_newDevAdded(uint8_t ID, uint8_t model, QString IP, uint16_t port);
    void on_newSettingReceived(uint16_t clientPort, QString clientIP);

    void on_newModelOutputGet();
    void on_addDeviceButton_clicked();
    void on_addModelButton_clicked();
    void on_actionShow_All_Models_triggered();
    void on_controllerMessageReceived(QByteArray msg);
    void on_actionSet_triggered();
    void on_actionShow_All_Devices_triggered();
};

#endif // MAINWINDOW_H
