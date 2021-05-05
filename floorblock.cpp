#include "floorblock.h"

FloorBlock::FloorBlock(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/world/sprites/world/floor-block.png"));
}
