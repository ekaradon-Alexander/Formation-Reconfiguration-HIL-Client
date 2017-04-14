#ifndef ADDMODELDIALOG_H
#define ADDMODELDIALOG_H

#include <QDialog>
#include <qstring.h>

namespace Ui {
class AddModelDialog;
}

class AddModelDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddModelDialog(QWidget *parent = 0);
    ~AddModelDialog();

signals:
    void sendNewModelData(uint8_t nModelState, uint8_t nModelControl, float deltat,
                          QString modelPath, QString modelName);

private slots:
    void on_buttonBox_accepted();

    void on_modelPath_clicked();

private:
    Ui::AddModelDialog *ui;
    QString modelPath;
};

#endif // ADDMODELDIALOG_H
