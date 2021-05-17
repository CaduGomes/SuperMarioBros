#define mod(x) ((x)>=0?(x):-(x))

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QObject>
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QDebug>
#include <QList>
#include <cmath>
#include "player.h"
#include "gamedirector.h"
#include "floor_block.h"
#include "mystery_block.h"
#include "brick_block.h"
#include "pipe_block.h"
#include "goomba_mob.h"
#include "flag_object.h"

extern GameDirector * gameDirector;

Player::Player(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/mario/sprites/mario/mario_parado.png"));

    mario_box_left = new QGraphicsRectItem(-8, 1, 8, 30, this);   // Setando hitbox da esquerda
    mario_box_right = new QGraphicsRectItem(32, 1, 8, 30, this);  // Setando hitbox da direita
    mario_box_top = new QGraphicsRectItem(1, -8, 30, 8, this);    // Setando hitbox do topo
    mario_box_bottom = new QGraphicsRectItem(1, 32, 30, 8, this); // Setando hitbox de baixo
    mario_box_precise_top = new QGraphicsRectItem(9, -1, 12, 1, this);
    mario_box_precise_bottom = new QGraphicsRectItem(7, 32, 16, 1, this);

    mario_box_bottom->setPen(Qt::NoPen); // Removendo pintura das hitboxes
    mario_box_left->setPen(Qt::NoPen);   // Removendo pintura das hitboxes
    mario_box_top->setPen(Qt::NoPen);    // Removendo pintura das hitboxes
    mario_box_right->setPen(Qt::NoPen);  // Removendo pintura das hitboxes
    mario_box_precise_top->setPen(Qt::NoPen);    // Removendo pintura das hitboxes
    mario_box_precise_bottom->setPen(Qt::NoPen);  // Removendo pintura das hitboxes

    timer = new QTimer(this);
    setZValue(999);

    jump = new QMediaPlayer(this);
    jump->setMedia(QUrl("qrc:/sounds/sounds/jump-small.wav"));


    win_music = new QMediaPlayer(this);
    win_music->setMedia(QUrl("qrc:/sounds/sounds/winning.wav"));

    music = new QMediaPlayer(this);
    music->setMedia(QUrl("qrc:/sounds/sounds/main-theme.mp3"));
    music->play();

    dead = new QMediaPlayer(this);
    dead->setMedia(QUrl("qrc:/sounds/sounds/mariodie.wav"));
}

void Player::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left && !stopControls)
        isMovingLeft = true;

    if (event->key() == Qt::Key_Right && !stopControls)
        isMovingRight = true;

    if (event->key() == Qt::Key_Space && !stopControls)
        isJumping = true;

}

void Player::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left && !stopControls)
        isMovingLeft = false;

    if (event->key() == Qt::Key_Right && !stopControls)
        isMovingRight = false;

    if (event->key() == Qt::Key_Space && !stopControls)
        isJumping = false;

}

void Player::movePlayer()
{
    if(stopControls)
        return;

    if (isMovingLeft && !stopControls){
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

    if(velX == 0 && !isJumping && !stopControls)
        stop_animation();

    if (isCollidingLeft && velX < 0)
        velX = 0;

    if (isCollidingRight && velX > 0)
        velX = 0;

    if (isCollidingBottom && velY > 0)
        velY = 0;

    if (isCollidingTop && velY < 0)
        velY = 0;

    if(win){
        if(x() > 6525){
            isAnimateToRight = false;
            isMovingRight = false;
            setZValue(-33);
            restart_game();
        }
    }

    if(y() > 450 && !isDead){
        dying();
    }

    setPos(x() + velX, y() + velY);

}

void Player::dying()
{
    if(!isDead){
        isDead = true;
        stopControls = true;
        music->stop();
        mario_direction = false;
        gravityMaxSpeed = 2;
        isMovingLeft = false;
        isMovingRight = false;
        isAnimateToLeft = false;
        isAnimateToRight = false;
        isJumping = false;
        isMidJump = false;
        setPixmap(QPixmap(":/mario/sprites/mario/mario_morrendo.png"));

        dead->play();
        velY = 0.5;
        timer = new QTimer(this)    ;
        connect(timer, &QTimer::timeout, this, &Player::die_animation_up);
        timer->start(20);

        QTimer::singleShot(4000,this, &Player::restart_game);
    }
}

void Player::colliding_block()
{
    if(stopControls)
        return;

    if (mario_box_bottom->collidingItems().size() > 0)
    {
        for (QGraphicsItem *colliding_item : mario_box_bottom->collidingItems())
        {
            if ((typeid(*colliding_item) == typeid(Mystery_Block) ||
                 typeid(*colliding_item) == typeid(Brick_Block) ||
                 typeid(*colliding_item) == typeid(Pipe_Block) ||
                 typeid(*colliding_item) == typeid(Floor_Block))
                    && colliding_item->y() - (y() + 32) < 0)
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
    }
    else
    {
        isCollidingBottom = false;
    }

    if (mario_box_top->collidingItems().size() > 0)
    {
        for (QGraphicsItem *colliding_item : mario_box_top->collidingItems())
        {
            if (typeid(*colliding_item) == typeid(Goomba_Mob))
            {
                dying();
            }

            if (typeid(*colliding_item) == typeid(Brick_Block))
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
            }
            else if ((typeid(*colliding_item) == typeid(Mystery_Block) ||
                      typeid(*colliding_item) == typeid(Pipe_Block) ||
                      typeid(*colliding_item) == typeid(Floor_Block)) &&
                     y() - (colliding_item->y() + static_cast<QGraphicsPixmapItem *>(colliding_item)->pixmap().height()) < 0)
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
    }
    else
    {
        isCollidingTop = false;
    }

    if (mario_box_right->collidingItems().size() > 0)
    {
        for (QGraphicsItem *colliding_item : mario_box_right->collidingItems())
        {
            if (typeid(*colliding_item) == typeid(Goomba_Mob))
            {
                dying();
            }

            if ((typeid(*colliding_item) == typeid(Mystery_Block) ||
                 typeid(*colliding_item) == typeid(Pipe_Block) ||
                 typeid(*colliding_item) == typeid(Floor_Block) ||
                 typeid(*colliding_item) == typeid(Brick_Block)) &&
                    colliding_item->x() - (x() + 32) < 0)
            {
                isCollidingRight = true;
            }
            else if(typeid(*colliding_item) == typeid(Flag_Object)){
                for(QGraphicsItem *flag_item : static_cast<Flag_Object *>(colliding_item)->body->collidingItems()){
                    if( typeid(*flag_item) == typeid(Player)){
                        if(!win){
                            winning_animation();
                            static_cast<Flag_Object *>(colliding_item)->winning();
                        }
                    }
                }
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
            if (typeid(*colliding_item) == typeid(Goomba_Mob))
            {
                dying();
            }

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
            else if ((typeid(*colliding_item) == typeid(Mystery_Block) ||
                      typeid(*colliding_item) == typeid(Pipe_Block) ||
                      typeid(*colliding_item) == typeid(Floor_Block)) &&
                     x() - (colliding_item->x() + static_cast<QGraphicsPixmapItem *>(colliding_item)->pixmap().width()) < 0)
            {
                isCollidingLeft = true;
            }
            else if(typeid(*colliding_item) == typeid(Flag_Object)){
                for(QGraphicsItem *flag_item : static_cast<Flag_Object *>(colliding_item)->body->collidingItems()){
                    if( typeid(*flag_item) == typeid(Player)){
                        if(!win){
                            winning_animation();
                            static_cast<Flag_Object *>(colliding_item)->winning();
                        }
                    }
                }
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

    if (mario_box_precise_top->collidingItems().size() > 0)
    {
        for (QGraphicsItem *colliding_item : mario_box_precise_top->collidingItems())
        {
            if (typeid(*colliding_item) == typeid(Mystery_Block))
            {
                static_cast<Mystery_Block *>(colliding_item)->open_box();
            }
            else if (typeid(*colliding_item) == typeid(Brick_Block))
            {
                static_cast<Brick_Block *>(colliding_item)->open_box(isBig);
            }
        }
    }

    if (mario_box_precise_bottom->collidingItems().size() > 0)
    {
        for (QGraphicsItem *colliding_item : mario_box_precise_bottom->collidingItems())
        {
            if (typeid(*colliding_item) == typeid(Goomba_Mob) && mod((x() + 16) - (colliding_item->x() + 16)) < 3)
            {
               static_cast<Goomba_Mob *>(colliding_item)->dead_animation();
            }
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

    if(!isAnimateToLeft && !isAnimateToRight)
        return;

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
    if(!isAnimateToLeft && !isAnimateToRight)
        return;

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
    if(!isAnimateToLeft && !isAnimateToRight)
        return;

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
    music->stop();
    mario_direction = false;
    stopControls = true;
    win = true;
    gravityMaxSpeed = 0.4;
    isMovingLeft = false;
    isMovingRight = false;
    isAnimateToLeft = false;
    isAnimateToRight = false;
    isJumping = false;
    isMidJump = false;
    setPos(6312, y());
    setPixmap(QPixmap(":/mario/sprites/mario/mario_deslizando_1.png"));

    QTimer::singleShot(2000,this, &Player::walk_winning_animation);

}

void Player::walk_winning_animation()
{
    setPos(x()+23, y());
    gravityMaxSpeed = 3;
    setPixmap(QPixmap(":/mario/sprites/mario/mario_deslizando_2.png").transformed(QTransform().scale(-1, 1)));
    QTimer::singleShot(100,this, &Player::walk_winning_animation_2);
}

void Player::walk_winning_animation_2()
{
    setPixmap(QPixmap(":/mario/sprites/mario/mario_parado.png").transformed(QTransform().scale(-1, 1)));
    QTimer::singleShot(20,this, &Player::walk_winning_animation_3);
}

void Player::walk_winning_animation_3()
{
    maxSpeed = 0.5;
    win_music->play();
    mario_direction = false;
    isMovingRight = true;
}

void Player::die_animation_up()
{
    if(y() < 270){
        timer->stop();
        velY = 0.2;
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &Player::die_animation_down);
        timer->start(20);
    }

    velY += 0.2;
    setPos(x(), y()-(2*velY));
}

void Player::die_animation_down()
{
     velY += 0.2;
     setPos(x(), y()+(2*velY));
}

void Player::restart_game()
{
    gameDirector->game_restart();
}
