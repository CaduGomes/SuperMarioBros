#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QMediaPlayer>

class Player: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Player(QGraphicsItem * parent = 0);

    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);
    void movePlayer();
    void dying();
    void colliding_block();
    bool getIsMovingRight() const;
    bool getIsMovingLeft() const;

private:
    float accl = 0.01;
    float maxSpeed = 1.5;
    float jumpCounterMax = 40;
    float jumpCounter = 0;
    float gravityMaxSpeed = 3;
    float velX = 0;
    float velY = 0;

    bool isBig = false;
    bool win = false;
    bool isTakingDamage = false;
    bool stopControls = false;
    bool stopGravity = false;
    bool isDead = false;
    bool isMovingRight = false;
    bool isMovingLeft = false;
    bool isCollidingRight = false;
    bool isCollidingLeft = false;
    bool isCollidingBottom = false;
    bool isCollidingTop = false;
    bool isJumping = false;
    bool mario_direction = false; //false = direita | true = esquerda
    bool isAnimateToRight = false;
    bool isAnimateToLeft = false;
    bool isMidJump = false;
    void damage();
    void get_powerup();
    void change_hitboxes();


    QGraphicsRectItem * mario_box_bottom;
    QGraphicsRectItem * mario_box_top;
    QGraphicsRectItem * mario_box_right;
    QGraphicsRectItem * mario_box_left;
    QGraphicsRectItem * mario_box_precise_top;
    QGraphicsRectItem * mario_box_precise_bottom;

    QTimer *timer;

    QMediaPlayer * jump;
    QMediaPlayer * win_music;
    QMediaPlayer * music;
    QMediaPlayer * dead;
    QMediaPlayer * kick;
    QMediaPlayer * powerup;
    QMediaPlayer * damage_music;

private slots:

    void walk_animation_1();
    void walk_animation_2();
    void walk_animation_3();
    void jump_animation();
    void stop_animation();
    void winning_animation();
    void walk_winning_animation();
    void walk_winning_animation_2();
    void walk_winning_animation_3();
    void damage_animation();
    void damage_animation_2();
    void stop_damage_animation();
    void powerup_animation();
    void powerup_animation_2();

    void die_animation_up();
    void die_animation_down();

    void restart_game();
};


#endif // PLAYER_H
