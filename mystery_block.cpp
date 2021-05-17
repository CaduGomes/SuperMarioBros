#include "mystery_block.h"

extern Game * game;

Mystery_Block::Mystery_Block(int surprise, QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/sprites/blocks/mystery-box/1.png"));
    surprise_selected = surprise;
    sprite_animation_1();

    bump = new QMediaPlayer(this);
    bump->setMedia(QUrl("qrc:/sounds/sounds/bump.wav"));
}

void Mystery_Block::open_box()
{
    if(!broken){
        bump->play();
        broken = true;
        setPixmap(QPixmap(":/sprites/blocks/mystery-box/open.png"));
        open_animation_start();
    }
}

void Mystery_Block::open_animation_start()
{
    setPos(x(), y()-6);

    switch (surprise_selected) {
        case mushroom:
         game->scene->addItem(new Mushroom_Object(x(), y()));
        break;

        case coin:
         game->scene->addItem(new Coin_Object(x(), y()));
        break;
    }

    QTimer::singleShot(200, this, &Mystery_Block::open_animation_end);
}

void Mystery_Block::open_animation_end()
{
    setPos(x(), y()+6);
}

void Mystery_Block::sprite_animation_1()
{
    if(!broken){
    setPixmap(QPixmap(":/sprites/blocks/mystery-box/1.png"));
    QTimer::singleShot(500, this, &Mystery_Block::sprite_animation_2);
    }
}

void Mystery_Block::sprite_animation_2()
{
    if(!broken){
    setPixmap(QPixmap(":/sprites/blocks/mystery-box/2.png"));
    QTimer::singleShot(150, this, &Mystery_Block::sprite_animation_3);
    }
}

void Mystery_Block::sprite_animation_3()
{
    if(!broken){
    setPixmap(QPixmap(":/sprites/blocks/mystery-box/3.png"));
    QTimer::singleShot(150, this, &Mystery_Block::sprite_animation_4);
    }
}

void Mystery_Block::sprite_animation_4()
{
    if(!broken){
    setPixmap(QPixmap(":/sprites/blocks/mystery-box/2.png"));
    QTimer::singleShot(150, this, &Mystery_Block::sprite_animation_1);
    }
}
