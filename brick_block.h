#ifndef BRICK_BLOCK_H
#define BRICK_BLOCK_H

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QDebug>

class Brick_Block: public QObject, public QGraphicsPixmapItem
{
public:
    Brick_Block(QGraphicsItem * parent = 0);
    void open_box();
private:
    int surprise_selected;
    bool broken;

};

#endif // BRICK_BLOCK_H
