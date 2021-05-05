#include "gamedirector.h"

GameDirector::GameDirector(QObject *parent) : QObject(parent)
{
    player = new Player();
    startTimer(30);
    player->setPos(0,0);
    // colocar o foco no jogador
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    // adicionar o jogad
}

void GameDirector::timerEvent(QTimerEvent *event)
{
    player->movePlayer();
    player->gravity();
}

Player *GameDirector::getPlayer() const
{
    return player;
}

void GameDirector::setPlayer(Player *value)
{
    player = value;
}
