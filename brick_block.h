#ifndef BRICK_BLOCK_H
#define BRICK_BLOCK_H

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QDebug>
#include <QMediaPlayer>

class Brick_Block: public QObject, public QGraphicsItemGroup
{
public:
    Brick_Block(QGraphicsItem * parent = 0);
    void open_box(bool isBig);
    QGraphicsPixmapItem * block;

private:
    int surprise_selected;
    bool broken;
    bool isAnimating = false;

    QGraphicsPixmapItem * piece1;
    QGraphicsPixmapItem * piece2;
    QGraphicsPixmapItem * piece3;
    QGraphicsPixmapItem * piece4;

    float velX = 3;
    float velY = -10;
    float velYdeBaixo = -8;

    QTimer *timer;

    QMediaPlayer * bump;

    QMediaPlayer * break_block;



public slots:
    void no_break_animation_start();
    void no_break_animation_end();
    void break_animation_start();
    void falling_animation_start();
};

#endif // BRICK_BLOCK_H
