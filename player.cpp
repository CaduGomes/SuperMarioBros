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
#include "pipe_block.h"
#include "flag_object.h"

Player::Player(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/mario/sprites/mario/mario_parado.png"));

    mario_box_left = new QGraphicsRectItem(-8, 1, 8, 30, this);   // Setando hitbox da esquerda
    mario_box_right = new QGraphicsRectItem(32, 1, 8, 30, this);  // Setando hitbox da direita
    mario_box_top = new QGraphicsRectItem(6, -4, 20, 4, this);    // Setando hitbox do topo
    mario_box_bottom = new QGraphicsRectItem(1, 32, 30, 8, this); // Setando hitbox de baixo

    //    mario_box_bottom->setPen(Qt::NoPen); // Removendo pintura das hitboxes
    //    mario_box_left->setPen(Qt::NoPen);   // Removendo pintura das hitboxes
    //    mario_box_top->setPen(Qt::NoPen);    // Removendo pintura das hitboxes
    //    mario_box_right->setPen(Qt::NoPen);  // Removendo pintura das hitboxes

    timer = new QTimer(this);

    jump = new QMediaPlayer(this);
    jump->setMedia(QUrl("qrc:/sounds/sounds/jump-small.wav"));

}

void Player::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left)
        isMovingLeft = true;

    if (event->key() == Qt::Key_Right)
        isMovingRight = true;

    if (event->key() == Qt::Key_Space)
        isJumping = true;

}

void Player::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left)
        isMovingLeft = false;

    if (event->key() == Qt::Key_Right)
        isMovingRight = false;

    if (event->key() == Qt::Key_Space)
        isJumping = false;

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

    if (!isMovingLeft && !isMovingRight)
        velX *= 0.9;

    if (!isMovingLeft && !isMovingRight && velX > -0.005 && velX < 0.005){
        velX = 0;
    }

    if (isJumping && jumpCounter < jumpCounterMax)
    {
        velY = -3;
        jumpCounter++;
        jump_animation();
        isMidJump = true;
    }

    else if (!isJumping && jumpCounter > 0)
    {
        jumpCounter = jumpCounterMax;
        isMidJump = false;
    }

    if (!isCollidingBottom && velY < gravityMaxSpeed)
    {
        velY += 0.15;
        if (!isMidJump)
            jumpCounter = jumpCounterMax;
    }

    if(velX == 0 && !isJumping)
        stop_animation();

    if (isCollidingLeft && velX < 0)
        velX = 0;

    if (isCollidingRight && velX > 0)
        velX = 0;

    if (isCollidingBottom && velY > 0)
        velY = 0;

    if (isCollidingTop && velY < 0)
        velY = 0;

    setPos(x() + velX, y() + velY);

}

void Player::colliding_block()
{
    if (mario_box_bottom->collidingItems().size() > 0)
    {
        for (QGraphicsItem *colliding_item : mario_box_bottom->collidingItems())
        {
            if (typeid(*colliding_item) == typeid(Mystery_Block) ||
                    typeid(*colliding_item) == typeid(Brick_Block) ||
                    typeid(*colliding_item) == typeid(Pipe_Block) ||
                    typeid(*colliding_item) == typeid(Floor_Block))
            {
                if (colliding_item->y() - (y() + 32) < 0)
                {
                    isCollidingBottom = true;
                    if (colliding_item->y() != y() + 32)
                        setPos(x(), colliding_item->y() - 32);

                    if (!isJumping)
                        jumpCounter = 0;
                }
                else
                {
                    isCollidingBottom = false;
                }
            }
            else
            {
                isCollidingBottom = false;
            }
        }
    }
    else
    {
        isCollidingBottom = false;
    }

    // Mario colidindo em cima
    if (mario_box_top->collidingItems().size() > 0)
    {
        for (QGraphicsItem *colliding_item : mario_box_top->collidingItems())
        {
            // Colidindo com mystery_block
            if (typeid(*colliding_item) == typeid(Mystery_Block))
            {
                static_cast<Mystery_Block *>(colliding_item)->open_box();
            }


            if (typeid(*colliding_item) == typeid(Mystery_Block) ||
                      typeid(*colliding_item) == typeid(Pipe_Block) ||
                      typeid(*colliding_item) == typeid(Floor_Block))
            {
                if (y() - (colliding_item->y() + static_cast<QGraphicsPixmapItem *>(colliding_item)->pixmap().height()) < 0)
                {
                    isCollidingTop = true;

                    if (isMidJump)
                        jumpCounter = jumpCounterMax;
                }
                else
                {
                    isCollidingTop = false;
                }
            }
            else if (typeid(*colliding_item) == typeid(Brick_Block))
            {
                if (y() - (colliding_item->y() + static_cast<Brick_Block *>(colliding_item)->block->pixmap().height()) < 0)
                {
                    isCollidingTop = true;

                    if (isMidJump)
                        jumpCounter = jumpCounterMax;
                }
                else
                {
                    isCollidingTop = false;
                }

                static_cast<Brick_Block *>(colliding_item)->open_box(isBig);
            }
            else
            {
                isCollidingTop = false;
            }
        }
    }
    else
    {
        isCollidingTop = false;
    }

    if (mario_box_right->collidingItems().size() > 0)
    {
        for (QGraphicsItem *colliding_item : mario_box_right->collidingItems())
        {
            if (typeid(*colliding_item) == typeid(Mystery_Block) ||
                    typeid(*colliding_item) == typeid(Pipe_Block) ||
                    typeid(*colliding_item) == typeid(Floor_Block) ||
                    typeid(*colliding_item) == typeid(Brick_Block))
            {
                if (colliding_item->x() - (x() + 32) < 0)
                {
                    isCollidingRight = true;
                }
                else
                {
                    isCollidingRight = false;
                }
            }
            else if(typeid(*colliding_item) == typeid(Flag_Object)){
                winning_animation();
                static_cast<Flag_Object *>(colliding_item)->winning();
            }
            else
            {
                isCollidingRight = false;
            }
        }
    }
    else
    {
        isCollidingRight = false;
    }

    if (mario_box_left->collidingItems().size() > 0)
    {
        for (QGraphicsItem *colliding_item : mario_box_left->collidingItems())
        {

            if (typeid(*colliding_item) == typeid(Brick_Block)){
                if (x() - (colliding_item->x() + static_cast<Brick_Block *>(colliding_item)->block->pixmap().width()) < 0)
                {
                    isCollidingLeft = true;
                }
                else
                {
                    isCollidingLeft = false;
                }
            }

            if (typeid(*colliding_item) == typeid(Mystery_Block) ||
                    typeid(*colliding_item) == typeid(Pipe_Block) ||
                    typeid(*colliding_item) == typeid(Floor_Block))
            {
                if (x() - (colliding_item->x() + static_cast<QGraphicsPixmapItem *>(colliding_item)->pixmap().width()) < 0)
                {
                    isCollidingLeft = true;
                }
                else
                {
                    isCollidingLeft = false;
                }
            }else if(typeid(*colliding_item) == typeid(Flag_Object)){
                winning_animation();
                static_cast<Flag_Object *>(colliding_item)->winning();
            }
            else
            {
                isCollidingLeft = false;
            }
        }
    }
    else
    {
        isCollidingLeft = false;
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
    jump->play();
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

void Player::winning_animation()
{
    mario_direction = false;
}

void Player::slide_winning_animation()
{

}

void Player::walk_winning_animation()
{

}
