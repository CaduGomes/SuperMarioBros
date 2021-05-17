#ifndef GAMEDIRECTOR_H
#define GAMEDIRECTOR_H

#include <QObject>
#include <QTimerEvent>
#include "game.h"
#include "player.h"

class GameDirector : public QObject
{
    Q_OBJECT
public:
    explicit GameDirector(Game * gameScreen = nullptr, QObject *parent = nullptr);
    void timerEvent(QTimerEvent *event);

    Player *getPlayer() const;
    void setPlayer(Player *value);

    void game_restart();
private:
    Player *player;
    Game * game;

signals:

};

#endif // GAMEDIRECTOR_H
