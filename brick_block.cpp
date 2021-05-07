#include "brick_block.h"

Brick_Block::Brick_Block(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/sprites/blocks/brick_normal.png"));
}

void Brick_Block::open_box()
{
     setPixmap(QPixmap(":/sprites/blocks/brick_broken.png"));
}
