#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QTimer>
#include <QPropertyAnimation>

class Player: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Player(QGraphicsItem * parent = 0);
    QTimer * timer;
    void keyPressEvent(QKeyEvent * event);

private:
    bool walking;
    QPropertyAnimation *animation;
};


#endif // PLAYER_H
