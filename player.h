#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
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

    bool getIsMovingRight() const;
    bool getIsMovingLeft() const;

private:
    float accl = 1.5;
    float maxSpeed = 20;
    float velX = 0;
    bool isMovingRight = false;
    bool isMovingLeft = false;
};


#endif // PLAYER_H
