#ifndef MUSHROOM_OBJECT_H
#define MUSHROOM_OBJECT_H

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QDebug>

class Mushroom_Object: public QObject, public QGraphicsPixmapItem
{
public:
    Mushroom_Object(qreal x, qreal y,QGraphicsItem * parent = 0);

private slots:
    void initial_animation();
    void start_movement();
    void movement_animation();

private:
    int initial_y;
    QTimer * timer;

    bool direction = true; // true = direita || false = esquerda
};

#endif // MUSHROOM_OBJECT_H
