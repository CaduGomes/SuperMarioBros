#include "goomba_mob.h"

Goomba_Mob::Goomba_Mob(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    walk_animation_1();
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
