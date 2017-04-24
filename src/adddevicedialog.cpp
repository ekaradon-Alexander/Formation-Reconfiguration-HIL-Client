#include "adddevicedialog.h"
#include "ui_adddevicedialog.h"

AddDeviceDialog::AddDeviceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDeviceDialog)
{
    ui->setupUi(this);
}

AddDeviceDialog::~AddDeviceDialog()
{
    delete ui;
}

void AddDeviceDialog::on_buttonBox_accepted()
{
    emit sendNewDevData(static_cast<uint8_t>(ui->ID->value()),
                        static_cast<uint8_t>(ui->model->currentIndex()),
                        ui->IP->text(),
                        static_cast<uint16_t>((ui->port->value())));
}

void AddDeviceDialog::addNewModelToCombo(uint8_t nState, uint8_t nControl, QString modelName)
{
    ui->model->addItem(modelName + " [" + QString::number(nState) + " state(s), "
                       + QString::number(nControl) + " input(s)]");
}

void AddDeviceDialog::incrementDeviceID(uint8_t currentDeviceNumber)
{
    ui->ID->setValue(currentDeviceNumber + 1);
}
