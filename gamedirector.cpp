#include "gamedirector.h"

GameDirector::GameDirector(QObject *parent) : QObject(parent)
{
    startTimer(30);
}

void GameDirector::timerEvent(QTimerEvent *event)
{
    player->movePlayer();
}

Player *GameDirector::getPlayer() const
{
    return player;
}

void GameDirector::setPlayer(Player *value)
{
    player = value;
}
