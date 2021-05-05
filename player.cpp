#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QObject>
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QDebug>
#include <QList>

#include "player.h"
#include "floorblock.h"

Player::Player(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/mario/sprites/mario/mario_parado.png"));
}

void Player::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left)
    {
        isMovingLeft = true;
    }
    else if (event->key() == Qt::Key_Right)
    {
        isMovingRight = true;
    }
}

void Player::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left)
    {
        isMovingLeft = false;
    }
    else if (event->key() == Qt::Key_Right)
    {
        isMovingRight = false;
    }
}

void Player::movePlayer()
{

    if (isMovingLeft)
    {
        velX -= velX >= maxSpeed * -1 ? accl : 0;
    }
    else if (isMovingRight)
    {
        velX += velX <= maxSpeed ? accl : 0;
    }
    else if (!isMovingLeft && !isMovingRight && velX < 0)
    {
        velX += accl;
    }
    else if (!isMovingLeft && !isMovingRight && velX > 0)
    {
        velX -= accl;
    }

    setPos(x() + velX, y());
}

void Player::gravity()
{
    qDebug() << tonochao;

    QList<QGraphicsItem *> colliding_item = collidingItems();

    if(colliding_item.size() == 0){
        tonochao = false;
    }

    for(int i = 0, n = colliding_item.size(); i < n; i++)
    {
        if(typeid(*(colliding_item[i])) == typeid(FloorBlock))
        {
            tonochao = true;
        }
    }


    if(!tonochao){
        setPos(x(), y()+8);
        return;
    }

    if(tonochao){
        setPos(x(), 300);
        return;
    }

}

bool Player::getIsMovingRight() const
{
    return isMovingRight;
}

bool Player::getIsMovingLeft() const
{
    return isMovingLeft;
}

