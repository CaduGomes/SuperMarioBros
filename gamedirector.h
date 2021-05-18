#ifndef GAMEDIRECTOR_H
#define GAMEDIRECTOR_H

#include <QObject>
#include <QTimerEvent>
#include "ISubject.h"
#include "iobserver.h"

class GameDirector : public QObject, public ISubject
{
    Q_OBJECT
public:
    explicit GameDirector(QObject *parent = nullptr);
    void timerEvent(QTimerEvent *event);

    void attach(IObserver *observer) override;
    void detach(IObserver *observer) override;

private:
    QList<IObserver *> obs_list;

};

#endif // GAMEDIRECTOR_H
