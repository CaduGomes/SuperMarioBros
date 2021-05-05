#ifndef FLOORBLOCK_H
#define FLOORBLOCK_H

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QObject>

class FloorBlock: public QObject, public QGraphicsPixmapItem
{
public:
    FloorBlock(QGraphicsItem * parent = 0);
};

#endif // FLOORBLOCK_H
