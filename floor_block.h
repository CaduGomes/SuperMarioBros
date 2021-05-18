#ifndef FLOOR_BLOCK_H
#define FLOOR_BLOCK_H

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QDebug>


class Floor_Block: public QObject, public QGraphicsPixmapItem
{
public:
    Floor_Block(qreal x, qreal y, bool terrain = true, QGraphicsItem * parent = 0);
};

#endif // FLOOR_BLOCK_H
