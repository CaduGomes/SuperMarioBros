#include "floor_block.h"

Floor_Block::Floor_Block(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/sprites/blocks/floor-block.png"));
    setZValue(10);
}
