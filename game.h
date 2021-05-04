#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include "player.h"

class Game : public QGraphicsView
{
public:
    Game(QWidget *parent = 0);

    QGraphicsScene * scene;
    Player * player;
};

#endif // GAME_H
