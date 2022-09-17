#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <trackinginfo.h>
#include "QFrame"
#include "QTimer"
#include "QSettings"

#include "writetofile.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    TrackingInfo *trackInf;
    QTimer *timer;
    WriteToFile *writeToFile;
    QSettings *setting;

private slots:
    void slotTimerAlarm();

    void on_pushButton_Start_clicked();

    void on_pushButton_Stop_clicked();

    void on_settingTime_triggered();

    void on_chooseFolder_triggered();

protected:
    void mouseMoveEvent(QMouseEvent *e) override;
};
#endif // MAINWINDOW_H
