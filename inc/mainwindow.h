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
    QTimer simTimer;

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
    QProcess *listenController;

    UDPThread *listenerThread;

private:
    void stateNoModel(void);
    void stateNoDevice(void);
    void stateNoMission(void);

private:
    bool validNewModel(uint8_t nState, uint8_t nControl, QString modelPath);
    void sendValidNewDevice(uint8_t ID, uint8_t model, QString IP, uint16_t port);

private slots:
    void on_newModelAdded(uint8_t nState, uint8_t nControl, float deltat,
                             QString modelPath, QString modelName);
    void on_newDevAdded(uint8_t ID, uint8_t model, QString IP, uint16_t port);
    void on_newSettingReceived(uint16_t clientPort, QString clientIP);
    void on_newMissionReceived(QVector<uint8_t> initialID, QVector<QString> initialData,
                               QVector<uint8_t> targetID, QVector<QString> targetData);

    void on_newModelOutputGet();
    void on_addDeviceButton_clicked();
    void on_addModelButton_clicked();
    void on_actionShow_All_Models_triggered();
    void on_controllerMessageReceived(QByteArray msg);
    void on_actionSet_triggered();
    void on_actionShow_All_Devices_triggered();
    void on_taskButton_clicked();
};

#endif // MAINWINDOW_H
