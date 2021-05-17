#include "gamedirector.h"
#include <QDebug>
#include <QApplication>
#include <QProcess>

GameDirector::GameDirector(Game * gameScreen, QObject *parent) : QObject(parent)
{
    game = gameScreen;
    startTimer(1000/167);
    player = new Player();
    player->setPos(0, 100);
    // colocar o foco no jogador
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    game->scene->addItem(player);

    goomba = new Goomba_Mob();
    goomba->setPos(1092, 200);

    game->scene->addItem(goomba);
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

void GameDirector::game_restart()
{
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}
