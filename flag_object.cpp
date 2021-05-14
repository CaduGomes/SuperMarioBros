#include "flag_object.h"

Flag_Object::Flag_Object(qreal x, qreal y, QGraphicsItem *parent): QGraphicsItemGroup(parent)
{
    body = new QGraphicsPixmapItem();
    body->setPixmap(QPixmap(":/sprites/world/flag-body.png"));

        addToGroup(body);

    flag = new QGraphicsPixmapItem();
    flag->setZValue(20);
    flag->setPixmap(QPixmap(":/sprites/world/flag.png"));
    flag->setPos(x-22,y-280);

    setPos(x,y-body->pixmap().height());
        addToGroup(flag);
}
