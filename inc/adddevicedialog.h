#ifndef ADDDEVICEDIALOG_H
#define ADDDEVICEDIALOG_H

#include <QDialog>

namespace Ui {
class AddDeviceDialog;
}

class AddDeviceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddDeviceDialog(QWidget *parent = 0);
    ~AddDeviceDialog();

signals:
    void sendNewDevData(uint8_t ID, uint8_t model, QString IP, uint16_t port);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AddDeviceDialog *ui;

public:
    void addNewModelToCombo(uint8_t nState, uint8_t nControl, QString modelName);
};

#endif // ADDDEVICEDIALOG_H
