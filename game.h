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
#include "player.h"
#include "iobserver.h"
#include "isubject.h"

class Game : public QGraphicsView, public IObserver
{
public:
    Game(ISubject &gLoop, QWidget *parent = 0);
    QGraphicsScene * scene;

    void check_mario_center_screen();
    void update() override;

private:
    void assemble_blocks();
    void assemble_scenery();
    void moveScreen(double quant);

    bool add_goomba1 = false;
    bool add_goomba2 = false;
    bool add_goomba3 = false;
    bool add_goomba4 = false;
    bool add_goomba5 = false;
    bool add_goomba6 = false;
    bool add_goomba7 = false;

    Player *player;
    ISubject &gameLoop;

    int floor = 416;
    int lvl1 = 288;

    int lvl2 = 160;
};

#endif // GAME_H
