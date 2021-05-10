#ifndef PIPE_BLOCK_H
#define PIPE_BLOCK_H

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QDebug>


class Pipe_Block: public QObject, public QGraphicsPixmapItem
{
public:
    Pipe_Block(QGraphicsItem * parent = 0);

    void setSize(int size);
private:
    int pipe_size = 3;
};

#endif // PIPE_BLOCK_H
