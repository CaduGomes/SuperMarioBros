#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QObject>
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QDebug>
#include <QList>
#include <cmath>
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

    timer = new QTimer(this);
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
    if (isMovingLeft){
        velX += ((-1 * maxSpeed) - velX) * accl;
        if(!isAnimateToLeft){
            isAnimateToLeft = true;
            isAnimateToRight = false;
            walk_animation_1();
        }
    }

    if (isMovingRight){
        velX += ((1 * maxSpeed) - velX) * accl;
        if(!isAnimateToRight){
            isAnimateToRight = true;
            isAnimateToLeft = false;
            walk_animation_1();
        }
    }

    if (!isMovingLeft && !isMovingRight && velX > -0.005 && velX < 0.005){
        velX = 0;

    }else if(!isMovingLeft && !isMovingRight){
        velX *= 0.9;
    }

    if (isJumping && jumpCounter < jumpCounterMax)
    {
        velY = -2;
        jumpCounter++;
        isFalling = false;
        jump_animation();
    }

    else if (!isJumping && jumpCounter > 0)
    {
        jumpCounter = jumpCounterMax;
        isFalling = true;
        jump_animation();
    }

    else
    {
        isFalling = true;
    }

    if (isFalling && velY < gravityMaxSpeed){
        velY += 0.1;
    }


    if(velX == 0 && !isJumping){
        stop_animation();
    }

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
            static_cast<Brick_Block *>(colliding_item)->open_box(true);
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

void Player::walk_animation_1()
{
    QPixmap pixmap =  QPixmap(":/mario/sprites/mario/mario_andando_1.png");

    if(isJumping){
        isAnimateToLeft = false;
        isAnimateToRight = false;
        return;
    }

    if(isAnimateToLeft){
        mario_direction = true;
        setPixmap(pixmap.transformed(QTransform().scale(-1, 1)));
        QTimer::singleShot(100, this, &Player::walk_animation_2);
    }

    if(isAnimateToRight){
        mario_direction = false;
        setPixmap(pixmap);
        QTimer::singleShot(100, this, &Player::walk_animation_2);
    }
}

void Player::walk_animation_2()
{
    QPixmap pixmap = QPixmap(":/mario/sprites/mario/mario_andando_2.png");

    if(isAnimateToLeft){
        setPixmap(pixmap.transformed(QTransform().scale(-1, 1)));
        QTimer::singleShot(100, this, &Player::walk_animation_3);
    }

    if(isAnimateToRight ){
        setPixmap(pixmap);
        QTimer::singleShot(100, this, &Player::walk_animation_3);
    }
}

void Player::walk_animation_3()
{
    QPixmap pixmap =  QPixmap(":/mario/sprites/mario/mario_andando_3.png");

    if(isAnimateToLeft){
        setPixmap(pixmap.transformed(QTransform().scale(-1, 1)));
    }

    if(isAnimateToRight ){
        setPixmap(pixmap);
    }

    isAnimateToLeft = false;
    isAnimateToRight = false;
}

void Player::jump_animation()
{
    QPixmap pixmap =  QPixmap(":/mario/sprites/mario/mario_pulando.png");

    if(mario_direction){
        setPixmap(pixmap.transformed(QTransform().scale(-1, 1)));
    }else {
        setPixmap(pixmap);
    }
}

void Player::stop_animation()
{
    QPixmap pixmap =  QPixmap(":/mario/sprites/mario/mario_parado.png");

    if(mario_direction){
        setPixmap(pixmap.transformed(QTransform().scale(-1, 1)));
    }else {
        setPixmap(pixmap);
    }
}
