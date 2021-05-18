#include "floor_block.h"

Floor_Block::Floor_Block(qreal x, qreal y, bool terrain, QGraphicsItem * parent): QGraphicsPixmapItem(parent)
{
    setZValue(10);
    if(!terrain){
        setPixmap(QPixmap(":/sprites/blocks/floor-block.png"));
    }else {
        setPixmap(QPixmap(":/sprites/blocks/terrain-block.png"));
    }

//    box = new QGraphicsRectItem

    setPos(x, y);
}
