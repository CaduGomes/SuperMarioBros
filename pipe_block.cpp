#include "pipe_block.h"

Pipe_Block::Pipe_Block(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/sprites/world/pipe.png"));
    setZValue(-1);
}

void Pipe_Block::setSize(int size)
{
    pipe_size = size;

    switch (size) {
    case 1:
        setPos(x(), y()-64);
        break;
    case 2:
        setPos(x(), y()-pixmap().height()+32);
        break;
    case 3:
        setPos(x(), y()-pixmap().height());
        break;
    }
}



