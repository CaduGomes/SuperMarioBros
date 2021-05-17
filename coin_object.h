#ifndef COIN_OBJECT_H
#define COIN_OBJECT_H

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QMediaPlayer>

class Coin_Object: public QObject, public QGraphicsPixmapItem
{
public:
    Coin_Object(qreal x, qreal y,QGraphicsItem * parent = 0);

private slots:
    void animation_2();
    void animation_3();
    void animation_4();
    void increasing_y_animation();
    void decreasing_y_animation();

private:
    QTimer * timer;

    int initial_y;
    float velY = 0.8;

    QMediaPlayer * coin;
};

#endif // COIN_OBJECT_H
