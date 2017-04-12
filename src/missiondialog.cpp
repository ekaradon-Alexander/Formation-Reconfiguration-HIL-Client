#include "missiondialog.h"
#include "ui_missiondialog.h"

MissionDialog::MissionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MissionDialog)
{
    ui->setupUi(this);

    ui->initialTableWidget->setColumnCount(3);
    ui->initialTableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("ID"));
    ui->initialTableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Model"));
    ui->initialTableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Initial status [x, y, h, ...]"));
    ui->initialTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->targetTableWidget->setColumnCount(3);
    ui->targetTableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("ID"));
    ui->targetTableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Model"));
    ui->targetTableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Target status [x, y, h, ...]"));
    ui->targetTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

MissionDialog::~MissionDialog()
{
    delete ui;
}

void MissionDialog::addNewItem(uint8_t ID, QString modelName)
{
    ui->initialTableWidget->setRowCount(ui->initialTableWidget->rowCount() + 1);
    ui->initialTableWidget->setItem(ui->initialTableWidget->rowCount() - 1, 0,
                                 new QTableWidgetItem(QString::number(ID)));
    ui->initialTableWidget->setItem(ui->initialTableWidget->rowCount() - 1, 1,
                                 new QTableWidgetItem(modelName));

    ui->targetTableWidget->setRowCount(ui->targetTableWidget->rowCount() + 1);
    ui->targetTableWidget->setItem(ui->targetTableWidget->rowCount() - 1, 0,
                                 new QTableWidgetItem(QString::number(ID)));
    ui->targetTableWidget->setItem(ui->targetTableWidget->rowCount() - 1, 1,
                                 new QTableWidgetItem(modelName));
}

void MissionDialog::on_buttonBox_accepted()
{
    QVector<QString> initialData;
    for (uint8_t i = 0; i < ui->initialTableWidget->rowCount(); i++)
    {
        initialData.append(ui->initialTableWidget->item(i, 2)->text());
    }
    QVector<QString> targetData;
    for (uint8_t i = 0; i < ui->targetTableWidget->rowCount(); i++)
    {
        targetData.append(ui->targetTableWidget->item(i, 2)->text());
    }
    emit sendNewMissionData(initialData, targetData);
}
