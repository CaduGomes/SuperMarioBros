#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QGraphicsItem>
#include <QTimer>

class Player: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Player(QGraphicsItem * parent = 0);
     QTimer * timer;
    void keyPressEvent(QKeyEvent * event);

private slots:
    void jump();
};

#endif // PLAYER_H
