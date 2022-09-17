#include "trackinginfo.h"
#include "qmath.h"
#include "QThread"

TrackingInfo::TrackingInfo()
{
    this->distance = 0;
    this->lastPoint.setX(-1);
    this->lastPoint.setY(-1);
    this->isCheck = false;
    this->time = 30;
}

TrackingInfo::TrackingInfo(int time) : TrackingInfo()
{
    if (time > 0) {
        this->time = time;
    }
}

void TrackingInfo::setLastPoint(QPointF value)
{
    this->lastPoint = value;
}

void TrackingInfo::calculateDistance(QPointF currentPoint)
{
    if (this->lastPoint.x() == -1 || this->lastPoint.y() == -1 ) {  // Начало расчета

        this->lastPoint.setX(currentPoint.x());
        this->lastPoint.setY(currentPoint.y());

    }
    else {

        float tempX = qPow(currentPoint.x() - this->lastPoint.x(), 2);
        float tempY = qPow(currentPoint.y() - this->lastPoint.y(), 2);
        this->distance += qSqrt(tempX + tempY);

        this->lastPoint = currentPoint;

    }
}

float TrackingInfo::getDistance()
{
    return this->distance;
}

void TrackingInfo::setIsCheck(bool value)
{
    this->isCheck = value;
}

bool TrackingInfo::getIsCheck()
{
    return this->isCheck;
}

int TrackingInfo::getTimeInSeconds()
{
    return this->time;
}

int TrackingInfo::getTimeInMilliseconds()
{
    return this->time * 1000; // Возращаем значение в миллисекундах
}

void TrackingInfo::setTime(int value)
{
    this->time = value;
}

void TrackingInfo::saveInfo(WriteToFile* writeToFile)
{
    writeToFile->addToQueue(this->distance);

    if (!writeToFile->isRunning()) {
       writeToFile->run();
    }

    this->distance = 0;
    this->lastPoint.setX(-1);
    this->lastPoint.setY(-1);
    this->isCheck = false;
}

void TrackingInfo::clearDistance()
{
    this->distance = 0;
}

