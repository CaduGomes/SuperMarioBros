#include "mushroom_object.h"
#include <QTimer>

Mushroom_Object::Mushroom_Object(qreal x, qreal y, QGraphicsItem * parent): QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/sprites/objects/power-up.png"));
    setZValue(-1);
    setPos(x,y-12);
    initial_y = y;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Mushroom_Object::initial_animation);
    timer->start(100);

    appears = new QMediaPlayer(this);
    appears->setMedia(QUrl("qrc:/sounds/sounds/powerup_appears.wav"));
    appears->play();
}

void Mushroom_Object::initial_animation()
{
    if((initial_y-32) == y()){
        timer->stop();
        start_movement();
    }else {
        setPos(x(), y()-4);
    }

}

void Mushroom_Object::start_movement()
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Mushroom_Object::movement_animation);
    timer->start(10);
}

void Mushroom_Object::movement_animation()
{
    setPos(x()+1.5, y());
}
