#ifndef TRACKINGINFO_H
#define TRACKINGINFO_H

#include "QPointF"
#include "QTime"
#include "writetofile.h"

class TrackingInfo
{
public:
    TrackingInfo();
    TrackingInfo(int);
    void setLastPoint(QPointF);
    void calculateDistance(QPointF);
    float getDistance();
    void setIsCheck(bool);
    bool getIsCheck();
    int getTimeInSeconds();
    int getTimeInMilliseconds();
    void setTime(int);
    void saveInfo(WriteToFile*);
    void clearDistance();

private:
    QPointF lastPoint; // Предыдущая точка, на которой находился курсор
    float distance; // Расстояние, пройденное курсором
    bool isCheck; // Можно ли рассчитывать расстояние (курсор находится в необходимой области и таймер включен)
    int time; // Интервал времени, за который измеряется расстояние (в секундах)
};

#endif // TRACKINGINFO_H
