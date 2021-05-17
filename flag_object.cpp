#include "flag_object.h"

Flag_Object::Flag_Object(qreal x, qreal y, QGraphicsItem *parent): QGraphicsItemGroup(parent)
{
    body = new QGraphicsPixmapItem();
    body->setPixmap(QPixmap(":/sprites/world/flag-body.png"));

    addToGroup(body);

    flag = new QGraphicsPixmapItem();
    flag->setZValue(20);
    flag->setPixmap(QPixmap(":/sprites/world/flag.png"));
    flag->setPos(x-26,y-280);
    setPos(x,y-body->pixmap().height());
    addToGroup(flag);

    flag_slide = new QMediaPlayer(this);
    flag_slide->setMedia(QUrl("qrc:/sounds/sounds/down_flagpole.wav"));
}

void Flag_Object::winning()
{
    if(!win){
        win = true;
        flag_slide->play();
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &Flag_Object::flag_going_down_animation);
        timer->start(10);
    }
}

void Flag_Object::flag_going_down_animation()
{
    if(flag->y() > 250)
        timer->stop();

    flag->setPos(flag->x(), flag->y()+4);
}
