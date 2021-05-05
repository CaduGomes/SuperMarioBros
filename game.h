#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include "floorblock.h"
#include <QVector>

class Game : public QGraphicsView
{
public:
    Game(QWidget *parent = 0);
    QGraphicsScene * scene;
    void check_mario_center_screen();

private:
    void moveScreen(double quant);
};

#endif // GAME_H
