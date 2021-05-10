#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QVector>

#include "floor_block.h"
#include "mystery_block.h"
#include "brick_block.h"

class Game : public QGraphicsView
{
public:
    Game(QWidget *parent = 0);
    QGraphicsScene * scene;
    void check_mario_center_screen();

private:
    void assemble_blocks();
    void assemble_scenery();
    void moveScreen(double quant);

    int floor = 416;
    int lvl1 = 288;

    int lvl2 = 160;
};

#endif // GAME_H
