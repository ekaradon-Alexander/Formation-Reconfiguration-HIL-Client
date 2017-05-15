#include "settingdialog.h"
#include "ui_settingdialog.h"

SettingDialog::SettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
    ui->port_spinBox->setValue(DEFAULT_CLIENT_PORT);
    refreshIPAddress();
    g_setting.clientIP = ui->ip_comboBox->currentText();
    g_setting.clientPort = ui->port_spinBox->value();
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::on_buttonBox_accepted()
{
    emit sendSettingData(static_cast<uint16_t>(ui->port_spinBox->value()),
                         ui->ip_comboBox->currentText(),
                         static_cast<uint16_t>(ui->plotting_spinBox->value()),
                         static_cast<uint16_t>(ui->control_spinBox->value()),
                         ui->outputDir->text());
}

void SettingDialog::refreshIPAddress(void)
{
    ui->ip_comboBox->clear();
    QList<QHostAddress> address = QNetworkInterface().allAddresses();
    for (uint8_t i = 0; i < address.length(); i++)
    {
        if (address.at(i).protocol() == QAbstractSocket::IPv4Protocol)
        {
            ui->ip_comboBox->addItem(address.at(i).toString());
        }
    }

    for (uint8_t i = 0; i < address.length(); i++)
    {
        if (g_setting.clientIP == address.at(i).toString())
        {
            ui->ip_comboBox->setCurrentText(g_setting.clientIP);
        }
    }
}

void SettingDialog::on_refresh_pushButton_clicked()
{
    refreshIPAddress();
}

void SettingDialog::showEvent(QShowEvent *)
{
    if (g_status == TASK_STATUS::NO_MODEL || g_status == TASK_STATUS::NO_DEVICE)
    {
        ui->network_groupBox->setEnabled(true);
        ui->network_groupBox->setTitle("Network");
    }
    else
    {
        ui->network_groupBox->setEnabled(false);
        ui->network_groupBox->setTitle("Network (available before add device)");
    }

    if (g_status == TASK_STATUS::SIMULATION)
    {
        ui->timer_groupBox->setEnabled(false);
        ui->timer_groupBox->setTitle("Timer (avaliable before start simulation)");
    }
    else
    {
        ui->timer_groupBox->setEnabled(true);
        ui->timer_groupBox->setTitle("Timer");
    }
}

void SettingDialog::on_outputDir_pushButton_clicked()
{
    QString tempOutputPath = QFileDialog::getExistingDirectory(this,
                                                               tr("Select Output File Directory"),
                                                               "./");
    this->ui->outputDir->setText(tempOutputPath);
}
