#ifndef BACKGROUND_IMAGE_H
#define BACKGROUND_IMAGE_H

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QDebug>
#include <QPixmap>

class Background_Image: public QObject, public QGraphicsPixmapItem
{
public:
    Background_Image(qreal x, qreal y, QPixmap imgURL, QGraphicsItem * parent = 0);
};

#endif // BACKGROUND_IMAGE_H
