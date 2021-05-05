#include "gamedirector.h"

GameDirector::GameDirector(QObject *parent) : QObject(parent)
{
    player = new Player();
    startTimer(30);
    player->setPos(0,300);
    // colocar o foco no jogador
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    // adicionar o jogad
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
