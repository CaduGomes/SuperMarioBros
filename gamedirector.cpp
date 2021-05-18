#include "gamedirector.h"
#include <QDebug>

GameDirector::GameDirector(QObject *parent) : QObject(parent)
{
    startTimer(1000/167);
}

void GameDirector::attach(IObserver *observer) {
    obs_list.push_back(observer);
}

void GameDirector::detach(IObserver *observer) {
    obs_list.removeOne(observer);
}

void GameDirector::timerEvent(QTimerEvent *event)
{
    for (IObserver *observer : obs_list)
    {
        observer->update();
    }
}
