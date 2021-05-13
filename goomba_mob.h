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

private:
    bool dead = false;

private slots:
    void walk_animation_1();
    void walk_animation_2();

};

#endif // GOOMBA_MOB_H
