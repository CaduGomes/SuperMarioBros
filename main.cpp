#include <QApplication>
#include "game.h"
#include "gamedirector.h"

Game * game;
GameDirector * gameDirector;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    gameDirector = new GameDirector();
    game = new Game(*gameDirector);
    game->show();
    return a.exec();
}
