#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QDateTime>
#include <QString>
#include <QTimer>
#include <QThread>
#include <QVector>
#include <QDebug>
#include <QProcess>
#include <QMessageBox>

#include <adddevicedialog.h>
#include <addmodeldialog.h>
#include <modelviewdialog.h>
#include <settingdialog.h>
#include <deviceviewdialog.h>
#include <missiondialog.h>

#include <uavmodel.h>
#include <uavdevice.h>
#include <mission.h>

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

    QTimer *plotTimer;
    QVector<QTimer *> modelTimers;

    AddDeviceDialog *addDeviceDialog;
    AddModelDialog *addModelDialog;
    ModelViewDialog *modelViewDialog;
    DeviceViewDialog *deviceViewDialog;
    SettingDialog *settingDialog;
    MissionDialog *missionDialog;

    QUdpSocket *sender;

    QVector<UAVModel *> models;
    QVector<UAVDevice *> devices;
    QVector<UAVDevice *> devicesWaitForValid;

    Mission *mission;

    QProcess *contactModel;
    QProcess *listenModelController;

    UDPThread *listenerThread;


private:    // about system state
    void stateNoModel(void);
    void stateNoDevice(void);
    void stateNoMission(void);
    void stateReady(void);

private:    // about validation
    bool validNewModel(uint8_t nModelState, uint8_t nModelControl, QString modelPath);
    void sendValidNewDevice(UAVDevice *device);

private:    // about simulation and plotting
    void initMap(void);
private slots:
    void updateMap(void);

private slots:
    void on_newModelAdded(uint8_t nModelState, uint8_t nModelControl, float deltat,
                             QString modelPath, QString modelName);
    void on_newDevAdded(uint8_t ID, uint8_t model, QString IP, uint16_t port);
    void on_newSettingReceived(uint16_t clientPort, QString clientIP);
    void on_newMissionReceived(QVector<uint8_t> initialID, QVector<QString> initialData,
                               QVector<uint8_t> targetID, QVector<QString> targetData);
    void on_controllerMessageReceived(QByteArray msg);
    void on_deviceSimTimeout(UAVDevice *device);

    void on_addDeviceButton_clicked();
    void on_addModelButton_clicked();
    void on_taskButton_clicked();
    void on_startButton_clicked();

    void on_actionShow_All_Models_triggered();
    void on_actionShow_All_Devices_triggered();
    void on_actionSet_triggered();

};

#endif // MAINWINDOW_H
