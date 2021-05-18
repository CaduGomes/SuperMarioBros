#ifndef MUSHROOM_OBJECT_H
#define MUSHROOM_OBJECT_H

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QMediaPlayer>

class Mushroom_Object: public QObject, public QGraphicsPixmapItem
{
public:
    Mushroom_Object(qreal x, qreal y,QGraphicsItem * parent = 0);

private slots:
    void initial_animation();

    void update();

private:
    void start_movement();

    int initial_y;
    QTimer * timer;

    float velY;

    float direction = 1;

    QMediaPlayer * appears;

    QGraphicsRectItem * collision_box_right;
    QGraphicsRectItem * collision_box_left;
    QGraphicsRectItem * collision_box_bottom;
};

#endif // MUSHROOM_OBJECT_H
