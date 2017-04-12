#ifndef MISSIONDIALOG_H
#define MISSIONDIALOG_H

#include <QDialog>
#include <QVector>

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
    void sendNewMissionData(QVector<QString> initialData, QVector<QString> targetData);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::MissionDialog *ui;
};

#endif // MISSIONDIALOG_H
