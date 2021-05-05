#ifndef GAMEDIRECTOR_H
#define GAMEDIRECTOR_H

#include <QObject>
#include <QTimerEvent>

#include "player.h"

class GameDirector : public QObject
{
    Q_OBJECT
public:
    explicit GameDirector(QObject *parent = nullptr);
    void timerEvent(QTimerEvent *event);

    Player *getPlayer() const;
    void setPlayer(Player *value);

private:
    Player *player;

signals:

};

#endif // GAMEDIRECTOR_H
