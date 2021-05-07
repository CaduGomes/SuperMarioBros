#include "mystery_block.h"

extern Game * game;

Mystery_Block::Mystery_Block(int surprise, QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/sprites/blocks/box_normal.png"));
    surprise_selected = surprise;
}

void Mystery_Block::open_box()
{
    if(!broken){
        broken = true;
        setPixmap(QPixmap(":/sprites/blocks/box_open.png"));
        animation_start();
    }
}

void Mystery_Block::animation_start()
{
    setPos(x(), y()-6);

    QTimer::singleShot(200, this, &Mystery_Block::animation_end);
}

void Mystery_Block::animation_end()
{
    setPos(x(), y()+6);

    switch (surprise_selected) {
        case mushroom:
         game->scene->addItem(new Mushroom_Object(pos().x(), pos().y()));
        break;

        case coin:
         game->scene->addItem(new Coin_Object(pos().x(), pos().y()));
        break;
    }


}
