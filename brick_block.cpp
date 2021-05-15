#include "brick_block.h"
#include <QTimer>

Brick_Block::Brick_Block(QGraphicsItem *parent): QGraphicsItemGroup(parent)
{
    block = new QGraphicsPixmapItem();
    piece1 = new QGraphicsPixmapItem();
    piece2 = new QGraphicsPixmapItem();
    piece3 = new QGraphicsPixmapItem();
    piece4 = new QGraphicsPixmapItem();

    piece1->setPixmap(QPixmap(":/sprites/blocks/brick_broken_1.png"));
    piece2->setPixmap(QPixmap(":/sprites/blocks/brick_broken_2.png"));
    piece3->setPixmap(QPixmap(":/sprites/blocks/brick_broken_2.png"));
    piece4->setPixmap(QPixmap(":/sprites/blocks/brick_broken_1.png"));
    block->setPixmap(QPixmap(":/sprites/blocks/brick_normal.png"));

    piece2->setPos(32-piece1->pixmap().width(),0);
    piece3->setPos(0,32-piece1->pixmap().height());
    piece4->setPos(32-piece1->pixmap().width(),32-piece1->pixmap().height());

    piece1->setZValue(-2);
    piece2->setZValue(-2);
    piece3->setZValue(-2);
    piece4->setZValue(-2);

    addToGroup(block);
    addToGroup(piece1);
    addToGroup(piece2);
    addToGroup(piece3);
    addToGroup(piece4);

}

void Brick_Block::open_box(bool isBig)
{
    if(isAnimating)
        return;

    if(isBig){
        piece1->setZValue(10);
        piece2->setZValue(10);
        piece3->setZValue(10);
        piece4->setZValue(10);
        break_animation_start();
    }else {
        isAnimating = true;
        no_break_animation_start();
    }
}

void Brick_Block::no_break_animation_start()
{
    setPos(x(), y()-6);

    QTimer::singleShot(200, this, &Brick_Block::no_break_animation_end);
}

void Brick_Block::no_break_animation_end()
{
    setPos(x(), y()+6);
    isAnimating = false;
}

void Brick_Block::break_animation_start()
{
    isAnimating = true;
    removeFromGroup(block);
    block->setVisible(false);
    block->setEnabled(false);
    block->setActive(false);

    falling_animation_start();

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Brick_Block::falling_animation_start);
    timer->start(30);

}

void Brick_Block::falling_animation_start(){
    piece1->setPos(piece1->x()-velX, piece1->y()+velY);
    piece2->setPos(piece2->x()+velX, piece2->y()+velY);
    piece3->setPos(piece3->x()-velX, piece3->y()+velYdeBaixo);
    piece4->setPos(piece4->x()+velX, piece4->y()+velYdeBaixo);

    velY += 1;
    velYdeBaixo += 1.2;
    if(velX > 0.5){
        velX -= 0.1;
    }



    if(piece1->pos().y()  > 400){
        timer->stop();
        deleteLater();
    }
}
