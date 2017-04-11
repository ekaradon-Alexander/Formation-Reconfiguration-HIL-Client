#ifndef MODELVIEWDIALOG_H
#define MODELVIEWDIALOG_H

#include <QDialog>
#include <QStandardItem>
#include <qstring.h>

namespace Ui {
class ModelViewDialog;
}

class ModelViewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModelViewDialog(QWidget *parent = 0);
    ~ModelViewDialog();

private:
    Ui::ModelViewDialog *ui;

public:
    void addNewItem(QString modelName, float deltat, uint8_t nState, uint8_t nControl);
};

#endif // MODELVIEWDIALOG_H
