#ifndef GOOMBA_MOB_H
#define GOOMBA_MOB_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QTimerEvent>
#include <QTimer>
#include "iobserver.h"
#include "gamedirector.h"


class Goomba_Mob: public QObject, public QGraphicsPixmapItem, public IObserver
{
    Q_OBJECT
public:
    Goomba_Mob(ISubject &gameLoop, QGraphicsItem * parent = 0);

    void update() override;
    void dead_animation();
    bool dead = false;
private:
    ISubject &gameLoop;

    int direction = -1;
    float velY = 0;

    QGraphicsRectItem * collision_box_right;
    QGraphicsRectItem * collision_box_left;
    QGraphicsRectItem * collision_box_bottom;

private slots:
    void walk_animation_1();
    void walk_animation_2();
    void dead_animation_end();

};

#endif // GOOMBA_MOB_H
