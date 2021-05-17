#ifndef FLAG_OBJECT_H
#define FLAG_OBJECT_H

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsItemGroup>
#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QMediaPlayer>

class Flag_Object: public QObject, public QGraphicsItemGroup
{
public:
    Flag_Object(qreal x, qreal y, QGraphicsItem * parent = 0);

    void winning();

    QGraphicsPixmapItem * flag;
    QGraphicsPixmapItem * body;
private:
    qreal flag_x, flag_y;


    QTimer *timer;

    bool win = false;

    QMediaPlayer * flag_slide;

private slots:
    void flag_going_down_animation();

};

#endif // FLAG_OBJECT_H
