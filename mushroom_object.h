#ifndef MUSHROOM_OBJECT_H
#define MUSHROOM_OBJECT_H

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QMediaPlayer>
#include "iobserver.h"
#include "isubject.h"

class Mushroom_Object: public QObject, public QGraphicsPixmapItem, public IObserver
{
public:
    Mushroom_Object(qreal x, qreal y, ISubject &gameLoop, QGraphicsItem * parent = 0);

    void update() override;

private slots:
    void initial_animation();

private:
    bool movement = false;
    int initial_y;
    QTimer * timer;

    ISubject &gameLoop;

    float velY;

    float direction = 1;

    QMediaPlayer * appears;

    QGraphicsRectItem * collision_box_right;
    QGraphicsRectItem * collision_box_left;
    QGraphicsRectItem * collision_box_bottom;
};

#endif // MUSHROOM_OBJECT_H
