#include "addmodeldialog.h"
#include "ui_addmodeldialog.h"
#include <qfiledialog.h>

AddModelDialog::AddModelDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddModelDialog)
{
    ui->setupUi(this);
}

AddModelDialog::~AddModelDialog()
{
    delete ui;
}

void AddModelDialog::on_buttonBox_accepted()
{
    if (!modelPath.isEmpty())
    {
        emit sendNewModelData(static_cast<uint8_t>(ui->nState->value()),
                              static_cast<uint8_t>(ui->nControl->value()),
                              ui->deltat->value(),
                              this->modelPath,
                              ui->modelName->text());
    }
}

void AddModelDialog::on_modelPath_clicked()
{
    modelPath = QFileDialog::getOpenFileName(this,
                                             tr("Select model"),
                                             ".",
                                             tr("Executable File (*)"));
    ui->modelPathDisp->setText(modelPath);
}
