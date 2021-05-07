#include "coin_object.h"

Coin_Object::Coin_Object(qreal x, qreal y, QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/sprites/objects/coin/1.png"));
    animation_2();
    setZValue(-1);
    setPos(x,y-32);
    initial_y = y-32;

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Coin_Object::increasing_y_animation);
    timer->start(15);
}

void Coin_Object::animation_2()
{
    setPixmap(QPixmap(":/sprites/objects/coin/2.png"));
    QTimer::singleShot(80, this,  &Coin_Object::animation_3);
}

void Coin_Object::animation_3()
{
    setPixmap(QPixmap(":/sprites/objects/coin/3.png"));
    QTimer::singleShot(80, this,  &Coin_Object::animation_4);
}

void Coin_Object::animation_4()
{
    setPixmap(QPixmap(":/sprites/objects/coin/4.png"));
    QTimer::singleShot(80, this,  &Coin_Object::animation_2);
}

void Coin_Object::increasing_y_animation()
{

    if((initial_y-96) >= y()) {
        timer->stop();

        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &Coin_Object::decreasing_y_animation);
        timer->start(10);
    }else {
        setPos(x(), y()-1-velY);
        velY += 0.2;
    }
}

void Coin_Object::decreasing_y_animation()
{
    if((initial_y-50) <= y()) {
        timer->stop();

        deleteLater();
    }else {
        setPos(x(), y()+2.5);
    }
}

