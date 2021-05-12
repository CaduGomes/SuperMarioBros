#ifndef FLAG_OBJECT_H
#define FLAG_OBJECT_H

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include <QDebug>

class Flag_Object: public QObject, public QGraphicsPixmapItem
{
public:
    Flag_Object(qreal x, qreal y, QGraphicsItem * parent = 0);
private:
    qreal flag_x, flag_y;
    QGraphicsPixmapItem *flag;
};

#endif // FLAG_OBJECT_H
