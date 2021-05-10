#include "background_image.h"

Background_Image::Background_Image(qreal x, qreal y, QPixmap imgURL, QGraphicsItem * parent): QGraphicsPixmapItem(parent)
{
    setPixmap(imgURL);
    setPos(x,y-pixmap().height());
    setZValue(-1);
}
