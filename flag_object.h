#ifndef FLAG_OBJECT_H
#define FLAG_OBJECT_H

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsItemGroup>
#include <QObject>
#include <QTimer>
#include <QDebug>

class Flag_Object: public QObject, public QGraphicsItemGroup
{
public:
    Flag_Object(qreal x, qreal y, QGraphicsItem * parent = 0);
private:
    qreal flag_x, flag_y;
    QGraphicsPixmapItem *flag;
    QGraphicsPixmapItem * body;


private slots:
    void get_flag_animation();
    void flag_going_down_animation();

};

#endif // FLAG_OBJECT_H
