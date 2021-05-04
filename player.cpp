#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QObject>
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QDebug>
#include <QList>

#include "player.h"
#include "floorblock.h"
#include "game.h"

extern Game * game;

Player::Player(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/mario/sprites/mario/parado.png"));
    walking = false;

}

void Player::keyPressEvent(QKeyEvent *event)
{

    if(event->key() == Qt::Key_Left)
    {
        // limite para não sair da tela
        if(pos().x() > 0)
            setPos(x()-8,y());
    }
    else if(event->key() == Qt::Key_Right)
    {

        if(pos().x() + 64 < 800 ) {

            walking = true;
            setPos(x()+8,y());

        }
    }
    else if(event->key() == Qt::Key_Up)
    {
        if(pos().y() > 0)
            setPos(x(),y()-8);
    }

    else if(event->key() == Qt::Key_Down)
    {
        if(pos().y() + 64 < 600)
            setPos(x(),y()+8);
    }

    QList<QGraphicsItem *> colliding_item = collidingItems();

    for(int i = 0, n = colliding_item.size(); i < n; i++)
    {
        if(typeid(*(colliding_item[i]))== typeid(FloorBlock))
        {
            qDebug() << "Item tocou";
        }
    }



}

