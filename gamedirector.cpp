#include "gamedirector.h"

GameDirector::GameDirector(Game * gameScreen, QObject *parent) : QObject(parent)
{
    game = gameScreen;
    startTimer(1000/33);
    player = new Player();
    player->setPos(50,200);
    // colocar o foco no jogador
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    game->scene->addItem(player);
}

void GameDirector::timerEvent(QTimerEvent *event)
{
    player->movePlayer();
    player->gravity();
    game->check_mario_center_screen();
}

Player *GameDirector::getPlayer() const
{
    return player;
}

void GameDirector::setPlayer(Player *value)
{
    player = value;
}
