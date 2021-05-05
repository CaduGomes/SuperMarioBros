#include "gamedirector.h"

GameDirector::GameDirector(QObject *parent) : QObject(parent)
{
    startTimer(1000/33);
    player = new Player();
    player->setPos(50,200);
    // colocar o foco no jogador
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    // adicionar o jogador
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
