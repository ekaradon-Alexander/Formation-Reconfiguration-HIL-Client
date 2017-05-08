#ifndef DEVICEVIEWDIALOG_H
#define DEVICEVIEWDIALOG_H

#include <QDialog>

namespace Ui {
class DeviceViewDialog;
}

class DeviceViewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeviceViewDialog(QWidget *parent = 0);
    ~DeviceViewDialog();

public:
    void addNewItem(uint8_t ID, QString modelName, QString IP, uint16_t port);

signals:
    void sendReconnectButton(void);

private slots:
    void on_reconnectPushButton_clicked();

private:
    Ui::DeviceViewDialog *ui;
};

#endif // DEVICEVIEWDIALOG_H
