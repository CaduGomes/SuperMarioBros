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
    void assemble_screen();
    void moveScreen(double quant);
};

#endif // GAME_H
