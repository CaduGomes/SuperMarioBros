#ifndef GOOMBA_MOB_H
#define GOOMBA_MOB_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QTimer>


class Goomba_Mob: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Goomba_Mob(QGraphicsItem * parent = 0);

    void update();
    void dead_animation();
private:
    bool dead = false;
    int direction = -1;
    float velY = 0;

    QGraphicsRectItem * collision_box_right;
    QGraphicsRectItem * collision_box_left;
    QGraphicsRectItem * collision_box_bottom;

private slots:
    void walk_animation_1();
    void walk_animation_2();

};

#endif // GOOMBA_MOB_H
