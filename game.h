#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include "gamedirector.h"
#include "floorblock.h"
#include <QVector>

class Game : public QGraphicsView
{
public:
    Game(QWidget *parent = 0);

    QGraphicsScene * scene;
    GameDirector * gameDirector;
    QList <FloorBlock*> floorBlockList;
};

#endif // GAME_H
