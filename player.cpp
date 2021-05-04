#include "player.h"
#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QDebug>


Player::Player(QGraphicsItem *parent): QGraphicsRectItem(parent)
{
    qDebug()<<"Construct";
}

void Player::keyPressEvent(QKeyEvent *event)
{
    qDebug()<<"Key press detected";

    if(event->key() == Qt::Key_Left)
    {
        // limite para não sair da tela
        if(pos().x() > 0)
            setPos(x()-10,y());
    }
    else if(event->key() == Qt::Key_Right)
    {
        // limite para não sair da tela
        if(pos().x() + 100 < 800 )
            setPos(x()+10,y());
    }
    else if(event->key() == Qt::Key_Up)
    {
            timer->start(50);
        connect(timer,SIGNAL(timeout()),this,SLOT(jump()));
    }
    else if(event->key() == Qt::Key_Down)
    {
        setPos(x(),y()+10);
    }

}

void Player::jump()
{


    setPos(x(),y()-10);
    if(pos().y() < -10)
    {
        scene()->removeItem(this);
        delete this;
        qDebug()<<"Bullet removed";
    }
}
