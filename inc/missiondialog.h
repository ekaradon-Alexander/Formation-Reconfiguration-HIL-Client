#ifndef MISSIONDIALOG_H
#define MISSIONDIALOG_H

#include <QDialog>
#include <QVector>
#include <QMessageBox>
#include <exception>
#include <QDebug>
#include <assert.h>

namespace Ui {
class MissionDialog;
}

class MissionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MissionDialog(QWidget *parent = 0);
    ~MissionDialog();

public:
    void addNewItem(uint8_t ID, QString modelName);

signals:
    void sendNewMissionData(QVector<uint8_t> initialID, QVector<QString> initialData,
                            float targetCenterVelocy, float targetCenterDirection,
                            QVector<uint8_t> targetID, QVector<QString> targetData);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::MissionDialog *ui;
};

#endif // MISSIONDIALOG_H
