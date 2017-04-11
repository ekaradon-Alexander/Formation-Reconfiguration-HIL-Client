#include "modelviewdialog.h"
#include "ui_modelviewdialog.h"

ModelViewDialog::ModelViewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModelViewDialog)
{
    ui->setupUi(this);
    ui->viewTableWidget->setColumnCount(4);
    ui->viewTableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Model Name"));
    ui->viewTableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Delta t [s]"));
    ui->viewTableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("#state"));
    ui->viewTableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("#control"));

    ui->viewTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

ModelViewDialog::~ModelViewDialog()
{
    delete ui;
}

void ModelViewDialog::addNewItem(QString modelName, float deltat, uint8_t nState, uint8_t nControl)
{
    ui->viewTableWidget->setRowCount(ui->viewTableWidget->rowCount() + 1);
    ui->viewTableWidget->setItem(ui->viewTableWidget->rowCount() - 1, 0,
                             new QTableWidgetItem(modelName));
    ui->viewTableWidget->setItem(ui->viewTableWidget->rowCount() - 1, 1,
                             new QTableWidgetItem(QString::number(deltat, 'g', 3)));
    ui->viewTableWidget->setItem(ui->viewTableWidget->rowCount() - 1, 2,
                             new QTableWidgetItem(QString::number(nState)));
    ui->viewTableWidget->setItem(ui->viewTableWidget->rowCount() - 1, 3,
                             new QTableWidgetItem(QString::number(nControl)));
}
