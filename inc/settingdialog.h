#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include <common.h>
#include <QNetworkInterface>
#include <QFileDialog>

namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingDialog(QWidget *parent = 0);
    ~SettingDialog();

private:
    Ui::SettingDialog *ui;

signals:
    void sendSettingData(uint16_t clientPort, QString clientIP,
                         uint16_t plottingTime, uint16_t controlTime,
                         QString outputDir);
private slots:
    void on_buttonBox_accepted();
    void on_refresh_pushButton_clicked();

    void on_outputDir_pushButton_clicked();

public:
    void refreshIPAddress(void);

private:
    void showEvent(QShowEvent *);
};

#endif // SETTINGDIALOG_H
