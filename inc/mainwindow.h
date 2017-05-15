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
#include <QFile>

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
    QTimer *controlTimer;

    QTimer *recorderTimer;
    uint64_t recorderTimerTickCount;

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

    QVector<QVector<double>> minimapXdata;
    QVector<QVector<double>> minimapYdata;

    QVector<QColor> colorList;

    QFile *outputFile;
    QTextStream *os;

    float devicePredictLoc[MAX_DEVICE_NUMBER][PREDICT_HORIZON][LOC_STATE_NUMBER];

private:    // about system state
    void stateNoModel(void);
    void stateNoDevice(void);
    void stateNoMission(void);
    void stateReady(void);
    void stateSimulation(void);
    void stateStop(void);

private:    // about validation
    bool validNewModel(uint8_t nModelState, uint8_t nModelControl, QString modelPath);
    void sendValidNewDevice(UAVDevice *device);

private:    // about simulation and plotting
    void initMap(void);
    void broadcastStates(void);
    void updateMap(void);
    void uploadMission(void);

private slots:
    void on_newModelAdded(uint8_t nModelState, uint8_t nModelControl, float deltat,
                             QString modelPath, QString modelName);
    void on_newDevAdded(uint8_t ID, uint8_t model, QString IP, uint16_t port);
    void on_newSettingReceived(uint16_t clientPort, QString clientIP,
                               uint16_t plittingTime, uint16_t controlTime,
                               QString outputDir);
    void on_newMissionReceived(QVector<uint8_t> initialID, QVector<QString> initialData,
                               float targetCenterVelocy,
                               float targetCenterDirection,
                               QVector<uint8_t> targetID, QVector<QString> targetData);
    void on_controllerMessageReceived(QByteArray msg);
    void on_reconnectMessageReceived(void);

    void on_plotTimerTimeout();
    void on_controlTimerTimeout();
    void on_recorderTimerTimeout();

    void on_actionShow_All_Models_triggered();
    void on_actionShow_All_Devices_triggered();
    void on_actionSet_triggered();

    void on_actionAbout_triggered();
    void on_actionAdd_Model_triggered();
    void on_actionAdd_Device_triggered();
    void on_actionMission_triggered();
    void on_actionStart_triggered();
    void on_actionStop_triggered();
};

#endif // MAINWINDOW_H
