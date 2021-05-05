#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPolygonItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>

class Player: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Player(QGraphicsItem * parent = 0);

    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);
    void movePlayer();
    void gravity();

    bool getIsMovingRight() const;
    bool getIsMovingLeft() const;
private:
    float accl = 1.2;
    float maxSpeed = 10;
    float velX = 0;
    float velY = 0;
    bool isMovingRight = false;
    bool isMovingLeft = false;

    QGraphicsRectItem * mario_box_bottom;
    QGraphicsRectItem * mario_box_top;
    QGraphicsRectItem * mario_box_right;
    QGraphicsRectItem * mario_box_left;
};


#endif // PLAYER_H
