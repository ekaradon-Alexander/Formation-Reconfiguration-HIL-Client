#include "deviceviewdialog.h"
#include "ui_deviceviewdialog.h"

DeviceViewDialog::DeviceViewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeviceViewDialog)
{
    ui->setupUi(this);
    ui->viewTableWidget->setColumnCount(4);
    ui->viewTableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("ID"));
    ui->viewTableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("model"));
    ui->viewTableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("IP"));
    ui->viewTableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("port"));

    ui->viewTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

DeviceViewDialog::~DeviceViewDialog()
{
    delete ui;
}

void DeviceViewDialog::addNewItem(uint8_t ID, QString modelName, QString IP, uint16_t port)
{
    ui->viewTableWidget->setRowCount(ui->viewTableWidget->rowCount() + 1);
    ui->viewTableWidget->setItem(ui->viewTableWidget->rowCount() - 1, 0,
                                 new QTableWidgetItem(QString::number(ID)));
    ui->viewTableWidget->setItem(ui->viewTableWidget->rowCount() - 1, 1,
                                 new QTableWidgetItem(modelName));
    ui->viewTableWidget->setItem(ui->viewTableWidget->rowCount() - 1, 2,
                                 new QTableWidgetItem(IP));
    ui->viewTableWidget->setItem(ui->viewTableWidget->rowCount() - 1, 3,
                                 new QTableWidgetItem(QString::number(port)));
}
