#ifndef ISUBJECT_H
#define ISUBJECT_H

#include "iobserver.h"

class ISubject {
 public:
  virtual void attach(IObserver *observer) = 0;
  virtual void detach(IObserver *observer) = 0;
};

#endif // ISUBJECT_H
