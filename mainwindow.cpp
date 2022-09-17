#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMouseEvent"
#include "QFileDialog"
#include "QInputDialog"
#include "QDebug"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setting = new QSettings("./settings.ini", QSettings::IniFormat);

    trackInf = new TrackingInfo(setting->value("time").toInt());
    writeToFile = new WriteToFile(setting->value("folder").toString());

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(slotTimerAlarm()));

    // Для отслеживания курсора без зажатия кнопки мыши
    setMouseTracking(true);
    ui->centralwidget->setMouseTracking(true);
    ui->mouseTracking->setMouseTracking(true);

    ui->X->setAlignment(Qt::AlignCenter);
    ui->Y->setAlignment(Qt::AlignCenter);
    ui->distance->setAlignment(Qt::AlignCenter);

    ui->pushButton_Stop->setEnabled(false);

}

MainWindow::~MainWindow()
{
    writeToFile->wait(); // Ожидаем, пока дозапишется информация в файл

    delete writeToFile;
    delete trackInf;
    delete ui;
}

void MainWindow::slotTimerAlarm()
{
    trackInf->saveInfo(writeToFile); // Сохранение информации в файл
    ui->distance->setText(QString("%1").arg(trackInf->getDistance())); // Обновление информации на UI
    timer->start(trackInf->getTimeInMilliseconds()); // Обновление таймера
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{

    QPointF pntMW = e->position(); // Координаты относительно MainWindow
    QPointF pntTracking; // Координаты области отслеживания

    if (timer->isActive()) { // Если таймер остановлен, то перемещения не фиксируются

        // Координаты области отслеживания курсора в координатах MainWindow
        float startWidth = ui->mouseTracking->x();
        float endWidth = ui->mouseTracking->x() + ui->mouseTracking->width();
        float startHeight = ui->mouseTracking->y();
        float endHeight = ui->mouseTracking->y() + ui->mouseTracking->height();

        // Если курсор в области отслеживания, то можно производить расчет пройденного расстояния
        if (pntMW.x() >= startWidth && pntMW.x() <= endWidth &&
                pntMW.y() >= startHeight && pntMW.y() <= endHeight) {

            // Выводим координаты области отслеживания, а не MainWindow
            ui->X->setText(QString("%1").arg(pntMW.x() - startWidth)); // Выводим координаты области отслеживания, а не MainWindow
            pntTracking.setX(pntMW.x() - startWidth);
            ui->Y->setText(QString("%1").arg(pntMW.y() - startHeight));
            pntTracking.setY(pntMW.y() - startHeight);

            // Если курсор до этого был в области,, то можно производить расчет пройденного расстояния
            if (trackInf->getIsCheck()) {
                trackInf->calculateDistance(pntTracking);
                ui->distance->setText(QString("%1").arg(trackInf->getDistance()));
            }
            else { // Иначе нужно задать "точку возврата в область",
                   // чтобы к дистанции не прибавилось расстояние от "точки выхода из области"

                trackInf->setLastPoint(pntTracking);
            }

            trackInf->setIsCheck(true);
        }
        else
            trackInf->setIsCheck(false);

    }
    else { // Иначе запрещаем расчет расстояния
        trackInf->setIsCheck(false);
    }

    QMainWindow::mouseMoveEvent(e);

}

void MainWindow::on_pushButton_Start_clicked()
{
    trackInf->clearDistance(); // При возобновлении таймера время и расстояние обнуляется
    ui->distance->setText(QString("%1").arg(trackInf->getDistance())); // Обновление информации на UI
    timer->start(trackInf->getTimeInMilliseconds());

    ui->pushButton_Start->setEnabled(false);
    ui->pushButton_Stop->setEnabled(true);
}


void MainWindow::on_pushButton_Stop_clicked()
{
    timer->stop();
    ui->pushButton_Stop->setEnabled(false);
    ui->pushButton_Start->setEnabled(true);
}


void MainWindow::on_settingTime_triggered()
{
    int time = QInputDialog::getInt(this, "Ввод временного интервала", "Временной интервал:", trackInf->getTimeInSeconds(), 1, 3600, 1);
    trackInf->setTime(time);
    setting->setValue("time", time); // Запись обновленных данных в файл настроек
}


void MainWindow::on_chooseFolder_triggered()
{
   QString str = QFileDialog::getExistingDirectory(0, "Выбор папки", "");
   writeToFile->setFolder(str);
   setting->setValue("folder", str); // Запись обновленных данных в файл настроек
}

