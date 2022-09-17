#ifndef WRITETOFILE_H
#define WRITETOFILE_H

#include "QQueue"
#include "QThread"
#include "QString"

class WriteToFile : public QThread
{
public:
    WriteToFile();
    WriteToFile(QString);
    void addToQueue(int);
    void run();
    void setFolder(QString);

private:
    QQueue<float> queueToFile; // Очередь для записи расстояний в файл
    QString folder; // Путь к папке, куда будут сохраняться файлы
};

#endif // WRITETOFILE_H
