#include "flag_object.h"

Flag_Object::Flag_Object(qreal x, qreal y, QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/sprites/world/flag-body.png"));
    setPos(x,y-pixmap().height());

    flag = new QGraphicsPixmapItem(this);
    flag->setZValue(20);
    flag->setPixmap(QPixmap(":/sprites/world/flag.png"));
    flag->setPos(x+8,y-18);
}
