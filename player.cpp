#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QObject>
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QDebug>
#include <QList>

#include "player.h"
#include "floor_block.h"
#include "mystery_block.h"
#include "brick_block.h"

Player::Player(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{

    setPixmap(QPixmap(":/mario/sprites/mario/mario_parado.png"));

    mario_box_left = new QGraphicsRectItem(-8, 1, 8, 30, this);   // Setando hitbox da esquerda
    mario_box_right = new QGraphicsRectItem(32, 1, 8, 30, this);  // Setando hitbox da direita
    mario_box_top = new QGraphicsRectItem(1, -8, 30, 8, this);    // Setando hitbox do topo
    mario_box_bottom = new QGraphicsRectItem(1, 32, 30, 8, this); // Setando hitbox de baixo

    mario_box_bottom->setPen(Qt::NoPen); // Removendo pintura das hitboxes
    mario_box_left->setPen(Qt::NoPen);   // Removendo pintura das hitboxes
    mario_box_top->setPen(Qt::NoPen);    // Removendo pintura das hitboxes
    mario_box_right->setPen(Qt::NoPen);  // Removendo pintura das hitboxes
}

void Player::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left)
    {
        isMovingLeft = true;
    }

    if (event->key() == Qt::Key_Right)
    {
        isMovingRight = true;
    }

    if (event->key() == Qt::Key_Space)
    {
        isJumping = true;
    }
}

void Player::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left)
    {
        isMovingLeft = false;
    }

    if (event->key() == Qt::Key_Right)
    {
        isMovingRight = false;
    }

    if (event->key() == Qt::Key_Space)
    {
        isJumping = false;
    }
}

void Player::movePlayer()
{
    if (isMovingLeft)
        velX += ((-1 * maxSpeed) - velX) * accl;

    if (isMovingRight)
        velX += ((1 * maxSpeed) - velX) * accl;

    if (!isMovingLeft && !isMovingRight)
        velX *= 0.9;

    if (isJumping && jumpCounter < jumpCounterMax)
    {
        velY = -2;
        jumpCounter++;
        isFalling = false;
    }
    else if (!isJumping && jumpCounter > 0)
    {
        jumpCounter = jumpCounterMax;
        isFalling = true;
    }
    else
    {
        isFalling = true;
    }

    if (isFalling && velY < gravityMaxSpeed)
        velY += 0.1;

    setPos(x() + velX, y() + velY);
}

void Player::gravity()
{
    if (isFalling)
    {
        for (QGraphicsItem *colliding_item : mario_box_bottom->collidingItems())
        {
            if (typeid(*colliding_item) == typeid(Floor_Block))
            {
                setPos(x(), colliding_item->y() - 32);
                velY = 0;
                jumpCounter = 0;
                isFalling = false;
            }
        }
    }
}

void Player::colliding_block()
{
    // Mario colidindo em cima
    for (QGraphicsItem *colliding_item : mario_box_top->collidingItems())
    {
        // Colidindo com mystery_block
        if (typeid(*colliding_item) == typeid(Mystery_Block))
        {
            static_cast<Mystery_Block *>(colliding_item)->open_box();
            return;
        }

        // Colidindo com brick_block
        if (typeid(*colliding_item) == typeid(Brick_Block))
        {
            static_cast<Brick_Block *>(colliding_item)->open_box();
            return;
        }
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
