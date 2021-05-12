#ifndef MYSTERY_BLOCK_H
#define MYSTERY_BLOCK_H

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QPropertyAnimation>

#include "game.h"
#include "mushroom_object.h"
#include "coin_object.h"

enum Surprise {
    mushroom,
    coin
};

class Mystery_Block: public QObject, public QGraphicsPixmapItem
{
public:
    Mystery_Block( int surprise = 0, QGraphicsItem * parent = 0);

    void open_box();
private:
    int surprise_selected;
    bool broken;

    Mushroom_Object * mushroom_object;

public slots:

    void open_animation_start();
    void open_animation_end();

    void sprite_animation_1();

    void sprite_animation_2();

    void sprite_animation_3();

    void sprite_animation_4();

};

#endif // MYSTERY_BLOCK_H
