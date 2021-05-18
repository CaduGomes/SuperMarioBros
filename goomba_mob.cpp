#include "goomba_mob.h"
#include "floor_block.h"
#include "mystery_block.h"
#include "brick_block.h"
#include "pipe_block.h"

Goomba_Mob::Goomba_Mob(ISubject &gLoop, QGraphicsItem *parent) : QGraphicsPixmapItem(parent), gameLoop(gLoop)
{
    gameLoop.attach(this);

    walk_animation_1();
    startTimer(1000/167);
    collision_box_left = new QGraphicsRectItem(-8, 1, 8, 30, this);   // Setando hitbox da esquerda
    collision_box_right = new QGraphicsRectItem(32, 1, 8, 30, this);  // Setando hitbox da direita
    collision_box_bottom = new QGraphicsRectItem(1, 32, 30, 8, this); // Setando hitbox de baixo

    collision_box_left->setPen(Qt::NoPen);
    collision_box_right->setPen(Qt::NoPen);
    collision_box_bottom->setPen(Qt::NoPen);
}

void Goomba_Mob::update()
{
    if (collision_box_bottom->collidingItems().size() > 0)
    {
        for (QGraphicsItem *colliding_item : collision_box_bottom->collidingItems())
        {
            if ((typeid(*colliding_item) == typeid(Mystery_Block) ||
                 typeid(*colliding_item) == typeid(Pipe_Block) ||
                 typeid(*colliding_item) == typeid(Floor_Block) ||
                 typeid(*colliding_item) == typeid(Brick_Block))
                    && colliding_item->y() - (y() + 32) < 0)
            {
                velY = 0;
                if (colliding_item->y() != y() + 32)
                    setPos(x(), colliding_item->y() - 32);
            }
            else
            {
                velY += velY < 3 ? 0.15 : 0;
            }
        }
    }
    else
    {
        velY += velY < 3 ? 0.15 : 0;
    }

    if (collision_box_right->collidingItems().size() > 0)
    {
        for (QGraphicsItem *colliding_item : collision_box_right->collidingItems())
        {
            if ((typeid(*colliding_item) == typeid(Mystery_Block) ||
                 typeid(*colliding_item) == typeid(Pipe_Block) ||
                 typeid(*colliding_item) == typeid(Floor_Block) ||
                 typeid(*colliding_item) == typeid(Brick_Block))
                    && colliding_item->x() - (x() + 32) < 0)
            {
                direction = -1;
            }
        }
    }

    if (collision_box_left->collidingItems().size() > 0)
    {
        for (QGraphicsItem *colliding_item : collision_box_left->collidingItems())
        {
            if (typeid(*colliding_item) == typeid(Brick_Block)){
                if (x() - (colliding_item->x() + static_cast<Brick_Block *>(colliding_item)->block->pixmap().width()) < 0)
                    direction = 1;
            }
            else if ((typeid(*colliding_item) == typeid(Mystery_Block) ||
                      typeid(*colliding_item) == typeid(Pipe_Block) ||
                      typeid(*colliding_item) == typeid(Floor_Block))
                     && x() - (colliding_item->x() + static_cast<QGraphicsPixmapItem *>(colliding_item)->pixmap().width()) < 0)
            {
                direction = 1;
            }
        }
    }

    setPos(x() + (0.3 * direction), y() + velY);
}

void Goomba_Mob::walk_animation_1()
{
    if(!dead){
        setPixmap(QPixmap(":/mobs/goomba_1"));
        QTimer::singleShot(150, this, &Goomba_Mob::walk_animation_2);
    }
}

void Goomba_Mob::walk_animation_2()
{
    if(!dead){
        setPixmap(QPixmap(":/mobs/goomba_2"));
        QTimer::singleShot(150, this, &Goomba_Mob::walk_animation_1);
    }
};

void Goomba_Mob::dead_animation(){
    dead = true;
    setPixmap(QPixmap(":/mobs/goomba_dead"));
    QTimer::singleShot(800, this, &Goomba_Mob::dead_animation_end);
}

void Goomba_Mob::dead_animation_end(){
    gameLoop.detach(this);
    deleteLater();
}
