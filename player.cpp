#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QObject>
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QDebug>
#include <QList>
#include <QApplication>
#include <QProcess>
#include <cmath>
#include "player.h"
#include "floor_block.h"
#include "mystery_block.h"
#include "brick_block.h"
#include "pipe_block.h"
#include "goomba_mob.h"
#include "flag_object.h"
#include "mushroom_object.h"
#include "background_image.h"

Player::Player(ISubject &gLoop, QGraphicsItem *parent) : QGraphicsPixmapItem(parent), gameLoop(gLoop)
{
    gameLoop.attach(this);

    setPixmap(QPixmap(":/mario/sprites/mario/mario_parado.png"));

    mario_box_left = new QGraphicsRectItem(0, 1, 2, 30, this);   // Setando hitbox da esquerda
    mario_box_right = new QGraphicsRectItem(30, 1, 2, 30, this);  // Setando hitbox da direita
    mario_box_top = new QGraphicsRectItem(4, -1, 24, 1, this);    // Setando hitbox do topo
    mario_box_bottom = new QGraphicsRectItem(4, 32, 24, 1, this); // Setando hitbox de baixo
    mario_box_precise_top = new QGraphicsRectItem(9, -1, 12, 1, this);
    mario_box_precise_bottom = new QGraphicsRectItem(4, 38, 24, 1, this);


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

    damage_music = new QMediaPlayer(this);
    damage_music->setMedia(QUrl("qrc:/sounds/sounds/damage.wav"));

    powerup = new QMediaPlayer(this);
    powerup->setMedia(QUrl("qrc:/sounds/sounds/get_powerup.wav"));

    music = new QMediaPlayer(this);
    music->setMedia(QUrl("qrc:/sounds/sounds/main-theme.mp3"));
    music->play();

    kick = new QMediaPlayer(this);
    kick->setMedia(QUrl("qrc:/sounds/sounds/kick.wav"));

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

void Player::update()
{
    movePlayer();
    colliding_block();
}

void Player::movePlayer()
{
    if(stopGravity)
        return;


    if (isMovingLeft){
        velX += ((-1 * maxSpeed) - velX) * accl;
        if(!isAnimateToLeft){
            isAnimateToLeft = true;
            isAnimateToRight = false;
            walk_animation_1();
        }
    }

    if (isMovingRight)
    {
        velX += ((1 * maxSpeed) - velX) * accl;
        if(!isAnimateToRight){
            isAnimateToRight = true;
            isAnimateToLeft = false;
            walk_animation_1();
        }
    }

    if (!isMovingLeft && !isMovingRight)
        velX *= 0.9;

    if (!isMovingLeft && !isMovingRight && velX > -0.005 && velX < 0.005)
        velX = 0;

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

    if(velX == 0 && !isJumping && !win && !isTakingDamage)
        stop_animation();

    if (isCollidingLeft && velX < 0)
        velX = 0;

    if (isCollidingRight && velX > 0)
        velX = 0;

    if (isCollidingBottom && velY > 0)
        velY = 0;

    if (isCollidingTop && velY < 0)
        velY = 0;

    if(win)
    {
        if(x() > 6525){
            isAnimateToRight = false;
            isMovingRight = false;
            setZValue(-33);
            QTimer::singleShot(3500,this, &Player::restart_game);
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
        stopGravity = true;
        music->stop();
        mario_direction = false;
        gravityMaxSpeed = 2;
        isMovingLeft = false;
        isMovingRight = false;
        isAnimateToLeft = false;
        isAnimateToRight = false;
        isJumping = false;
        isMidJump = false;

        if(isBig){
            setPixmap(QPixmap(":/mario/sprites/mario/mario-big_morrendo.png"));

        }else {
            setPixmap(QPixmap(":/mario/sprites/mario/mario_morrendo.png"));
        }



        dead->play();
        velY = 0.5;
        timer = new QTimer(this)    ;
        connect(timer, &QTimer::timeout, this, &Player::die_animation_up);
        timer->start(20);

        QTimer::singleShot(4000, this, &Player::restart_game);
    }
}

void Player::colliding_block()
{
    if(stopGravity)
        return;

    if (mario_box_bottom->collidingItems().size() > 0)
    {
        for (QGraphicsItem *colliding_item : mario_box_bottom->collidingItems())
        {
            if (typeid(*colliding_item) == typeid(Background_Image))
            {
                isCollidingBottom = false;
                continue;
            }

            if (typeid(*colliding_item) == typeid(Mushroom_Object))
            {
                static_cast<Mushroom_Object *>(colliding_item)->deleteLater();
                get_powerup();
            }

            if (typeid(*colliding_item) == typeid(Mystery_Block) ||
                    typeid(*colliding_item) == typeid(Brick_Block) ||
                    typeid(*colliding_item) == typeid(Pipe_Block) ||
                    typeid(*colliding_item) == typeid(Floor_Block))
            {
                isCollidingBottom = true;

                if (colliding_item->y() != y() + pixmap().height())
                    setPos(x(), colliding_item->y() - pixmap().height());

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
            if (typeid(*colliding_item) == typeid(Mushroom_Object))
            {
                static_cast<Mushroom_Object *>(colliding_item)->deleteLater();
                get_powerup();
            }
            else if (typeid(*colliding_item) == typeid(Goomba_Mob))
            {
                if(!static_cast<Goomba_Mob *>(colliding_item)->dead){
                    damage();
                }
            }

            if (typeid(*colliding_item) == typeid(Mystery_Block) ||
                    typeid(*colliding_item) == typeid(Pipe_Block) ||
                    typeid(*colliding_item) == typeid(Floor_Block) ||
                    typeid(*colliding_item) == typeid(Brick_Block))
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
            if (typeid(*colliding_item) == typeid(Background_Image))
                continue;

            if (typeid(*colliding_item) == typeid(Mushroom_Object))
            {
                static_cast<Mushroom_Object *>(colliding_item)->deleteLater();
                get_powerup();
            }
            else if (typeid(*colliding_item) == typeid(Goomba_Mob))
            {
                if(!static_cast<Goomba_Mob *>(colliding_item)->dead){
                    damage();
                }
            }

            if (typeid(*colliding_item) == typeid(Mystery_Block) ||
                    typeid(*colliding_item) == typeid(Pipe_Block) ||
                    typeid(*colliding_item) == typeid(Floor_Block) ||
                    typeid(*colliding_item) == typeid(Brick_Block))
            {
                isCollidingRight = true;
            }
            else if(typeid(*colliding_item) == typeid(Flag_Object)){
                for(QGraphicsItem *flag_item : static_cast<Flag_Object *>(colliding_item)->body->collidingItems()){
                    if(typeid(*flag_item) == typeid(Player)){
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
            if (typeid(*colliding_item) == typeid(Background_Image))
                continue;

            if (typeid(*colliding_item) == typeid(Mushroom_Object))
            {
                static_cast<Mushroom_Object *>(colliding_item)->deleteLater();
                get_powerup();
            }
            else if (typeid(*colliding_item) == typeid(Goomba_Mob))
            {
                if(!static_cast<Goomba_Mob *>(colliding_item)->dead){
                    damage();
                }
            }

            if (typeid(*colliding_item) == typeid(Mystery_Block) ||
                    typeid(*colliding_item) == typeid(Pipe_Block) ||
                    typeid(*colliding_item) == typeid(Floor_Block) ||
                    typeid(*colliding_item) == typeid(Brick_Block))
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
            if (typeid(*colliding_item) == typeid(Goomba_Mob))
            {
                if(!static_cast<Goomba_Mob *>(colliding_item)->dead){
                    static_cast<Goomba_Mob *>(colliding_item)->dead_animation();
                    kick->play();
                }
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

void Player::damage()
{
    if(isTakingDamage)
        return;

    if(isBig){
        damage_music->play();
        isTakingDamage = true;
        QTimer::singleShot(0, this, &Player::damage_animation);
        QTimer::singleShot(200, this, &Player::damage_animation);
        QTimer::singleShot(400, this, &Player::damage_animation);
        QTimer::singleShot(600, this, &Player::damage_animation);
        QTimer::singleShot(1000, this, &Player::stop_damage_animation);
        isBig = false;
        change_hitboxes();

    }else {
        dying();
    }

}

void Player::get_powerup()
{
    if(isBig)
        return;

    powerup->play();
    setPos(x(), y()-32);
    setPixmap(QPixmap(":/mario/sprites/mario/mario-big_parado.png"));
    QTimer::singleShot(0, this, &Player::powerup_animation);
    QTimer::singleShot(200, this, &Player::powerup_animation);
    QTimer::singleShot(400, this, &Player::powerup_animation);
    QTimer::singleShot(600, this, &Player::powerup_animation);
    isBig = true;
    change_hitboxes();
}

void Player::change_hitboxes()
{
    if(isBig){
        mario_box_left = new QGraphicsRectItem(0, 1, 2, 62, this);   // Setando hitbox da esquerda
        mario_box_right = new QGraphicsRectItem(30, 1, 2, 62, this);  // Setando hitbox da direita
        mario_box_top = new QGraphicsRectItem(4, -1, 24, 1, this);    // Setando hitbox do topo
        mario_box_bottom = new QGraphicsRectItem(4, 64, 24, 1, this); // Setando hitbox de baixo
        mario_box_precise_top = new QGraphicsRectItem(9, -1, 12, 1, this);
        mario_box_precise_bottom = new QGraphicsRectItem(7, 64, 16, 1, this);
    }else {
        mario_box_left = new QGraphicsRectItem(0, 1, 2, 30, this);   // Setando hitbox da esquerda
        mario_box_right = new QGraphicsRectItem(30, 1, 2, 30, this);  // Setando hitbox da direita
        mario_box_top = new QGraphicsRectItem(4, -1, 24, 1, this);    // Setando hitbox do topo
        mario_box_bottom = new QGraphicsRectItem(4, 32, 24, 1, this); // Setando hitbox de baixo
        mario_box_precise_top = new QGraphicsRectItem(9, -1, 12, 1, this);
        mario_box_precise_bottom = new QGraphicsRectItem(7, 34, 16, 1, this);
    }

    mario_box_bottom->setPen(Qt::NoPen); // Removendo pintura das hitboxes
    mario_box_left->setPen(Qt::NoPen);   // Removendo pintura das hitboxes
    mario_box_top->setPen(Qt::NoPen);    // Removendo pintura das hitboxes
    mario_box_right->setPen(Qt::NoPen);  // Removendo pintura das hitboxes
    mario_box_precise_top->setPen(Qt::NoPen);    // Removendo pintura das hitboxes
    mario_box_precise_bottom->setPen(Qt::NoPen);  // Removendo pintura das hitboxes
}

void Player::walk_animation_1()
{
    QPixmap pixmap =  QPixmap(":/mario/sprites/mario/mario_andando_1.png");

    if(isBig)
        pixmap = QPixmap(":/mario/sprites/mario/mario-big_andando_1.png");

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

    if(isBig)
        pixmap = QPixmap(":/mario/sprites/mario/mario-big_andando_2.png");

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

    if(isBig)
        pixmap = QPixmap(":/mario/sprites/mario/mario-big_andando_3.png");

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

    if(isBig)
        pixmap = QPixmap(":/mario/sprites/mario/mario-big_pulando.png");

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

    if(isBig)
        pixmap = QPixmap(":/mario/sprites/mario/mario-big_parado.png");

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

    if(isBig){
        setPixmap(QPixmap(":/mario/sprites/mario/mario-big_deslizando_1.png"));
    }else {
        setPixmap(QPixmap(":/mario/sprites/mario/mario_deslizando_1.png"));
    }

    QTimer::singleShot(2000,this, &Player::walk_winning_animation);

}

void Player::walk_winning_animation()
{
    setPos(x()+23, y());
    gravityMaxSpeed = 3;

    if(isBig){
        setPixmap(QPixmap(":/mario/sprites/mario/mario-big_deslizando_2.png").transformed(QTransform().scale(-1, 1)));
    }else {
        setPixmap(QPixmap(":/mario/sprites/mario/mario_deslizando_2.png").transformed(QTransform().scale(-1, 1)));
    }

    QTimer::singleShot(100,this, &Player::walk_winning_animation_2);
}

void Player::walk_winning_animation_2()
{
    if(isBig){
        setPixmap(QPixmap(":/mario/sprites/mario/mario-big_parado.png").transformed(QTransform().scale(-1, 1)));
    }else {
        setPixmap(QPixmap(":/mario/sprites/mario/mario_parado.png").transformed(QTransform().scale(-1, 1)));
    }

    QTimer::singleShot(20,this, &Player::walk_winning_animation_3);
}

void Player::walk_winning_animation_3()
{
    maxSpeed = 0.5;
    win_music->play();
    mario_direction = false;
    isMovingRight = true;

    QTimer::singleShot(20,this, &Player::walk_winning_animation_3);
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
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}

void Player::damage_animation(){
    QPixmap a = pixmap();
    a.fill(Qt::transparent);

    setPixmap(a);

    QTimer::singleShot(50, this, &Player::damage_animation_2);
}

void Player::damage_animation_2()
{
    setPixmap(QPixmap(":/mario/sprites/mario/mario_parado.png"));
}

void Player::stop_damage_animation()
{
    isTakingDamage = false;
}

void Player::powerup_animation()
{
    QPixmap a = pixmap();
    a.fill(Qt::transparent);
    setPixmap(a);
    QTimer::singleShot(100, this, &Player::powerup_animation_2);
}

void Player::powerup_animation_2()
{
    setPixmap(QPixmap(":/mario/sprites/mario/mario-big_parado.png"));
}
