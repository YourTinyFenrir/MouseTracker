#include "writetofile.h"
#include "QFile"
#include "QDateTime"
#include "QString"
#include "QTextStream"

WriteToFile::WriteToFile()
{

}

WriteToFile::WriteToFile(QString folder) : WriteToFile()
{
    if (!folder.isEmpty()) {
        this->folder = folder;
    }
}

void WriteToFile::addToQueue(int value)
{
    this->queueToFile.append(value);
}

void WriteToFile::run()
{
    while (!this->queueToFile.empty()) {

        QString fileName(QDateTime::currentDateTimeUtc().toString());
        fileName.replace(":", "-"); // В названии файла запрещено использование :

        QFile file(this->folder + "/" + fileName + ".txt");

        file.open(QIODevice::WriteOnly);

        QTextStream writeStream(&file);
        writeStream << this->queueToFile.dequeue();
        file.close();

    }
}

void WriteToFile::setFolder(QString str)
{
    this->folder = str;
}
