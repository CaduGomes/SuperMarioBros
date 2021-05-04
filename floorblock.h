#ifndef FLOORBLOCK_H
#define FLOORBLOCK_H

#include <QGraphicsRectItem>
#include <QObject>

class FloorBlock: public QObject, public QGraphicsRectItem
{
public:
    FloorBlock(QGraphicsItem * parent = 0);
};

#endif // FLOORBLOCK_H
