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
    void gravity();
    void colliding_block();
    bool getIsMovingRight() const;
    bool getIsMovingLeft() const;

private:
    float accl = 0.01;
    float maxSpeed = 1.5;
    float jumpCounterMax = 60;
    float jumpCounter = 0;
    float gravityMaxSpeed = 3;
    float velX = 0;
    float velY = 0;

    bool isMovingRight = false;
    bool isMovingLeft = false;
    bool isJumping = false;
    bool isFalling = false;
    bool mario_direction = false; //false = direita | true = esquerda
    bool isAnimateToRight = false;
    bool isAnimateToLeft = false;

    QGraphicsRectItem * mario_box_bottom;
    QGraphicsRectItem * mario_box_top;
    QGraphicsRectItem * mario_box_right;
    QGraphicsRectItem * mario_box_left;

    QTimer *timer;

private slots:

    void walk_animation_1();
    void walk_animation_2();
    void walk_animation_3();
    void jump_animation();
    void stop_animation();
};


#endif // PLAYER_H
