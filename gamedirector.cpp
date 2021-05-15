#include "gamedirector.h"
#include <QDebug>

GameDirector::GameDirector(Game * gameScreen, QObject *parent) : QObject(parent)
{
    game = gameScreen;
    startTimer(1000/167);
    player = new Player();
    player->setPos(50, 200);
    // colocar o foco no jogador
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    game->scene->addItem(player);
}

void GameDirector::timerEvent(QTimerEvent *event)
{
    player->movePlayer();
    game->check_mario_center_screen();
    player->colliding_block();
}

Player *GameDirector::getPlayer() const
{
    return player;
}

void GameDirector::setPlayer(Player *value)
{
    player = value;
}
