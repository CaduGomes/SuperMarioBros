#include <QApplication>
#include "game.h"
#include "gamedirector.h"

Game * game;
GameDirector * gameDirector;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    game = new Game();
    gameDirector = new GameDirector(game);
    game->show();
    return a.exec();
}
