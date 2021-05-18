#include "mushroom_object.h"
#include "floor_block.h"
#include "mystery_block.h"
#include "brick_block.h"
#include "pipe_block.h"
#include <QTimer>

Mushroom_Object::Mushroom_Object(qreal x, qreal y, ISubject &gLoop, QGraphicsItem * parent): QGraphicsPixmapItem(parent), gameLoop(gLoop)
{
    gameLoop.attach(this);

    setPixmap(QPixmap(":/sprites/objects/power-up.png"));
    setZValue(-1);
    setPos(x, y - 12);
    initial_y = y;

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Mushroom_Object::initial_animation);
    timer->start(100);

    appears = new QMediaPlayer(this);
    appears->setMedia(QUrl("qrc:/sounds/sounds/powerup_appears.wav"));
    appears->play();

    collision_box_left = new QGraphicsRectItem(-1, 1, 1, 30, this);   // Setando hitbox da esquerda
    collision_box_right = new QGraphicsRectItem(32, 1, 1, 30, this);  // Setando hitbox da direita
    collision_box_bottom = new QGraphicsRectItem(1, 32, 30, 1, this); // Setando hitbox de baixo

    collision_box_left->setPen(Qt::NoPen);
    collision_box_right->setPen(Qt::NoPen);
    collision_box_bottom->setPen(Qt::NoPen);
}

void Mushroom_Object::update()
{
    if (!movement)
        return;

    if (collision_box_bottom->collidingItems().size() > 0)
    {
        for (QGraphicsItem *colliding_item : collision_box_bottom->collidingItems())
        {
            if (typeid(*colliding_item) == typeid(Mystery_Block) ||
                    typeid(*colliding_item) == typeid(Pipe_Block) ||
                    typeid(*colliding_item) == typeid(Floor_Block) ||
                    typeid(*colliding_item) == typeid(Brick_Block))
            {
                velY = 0;
                if (colliding_item->y() != y() + 32)
                    setPos(x(), colliding_item->y() - 32);
            }
            else
            {
                velY += velY < 3 ? 0.15 : 0;
            }
        }
    }
    else
    {
        velY += velY < 3 ? 0.15 : 0;
    }

    if (collision_box_right->collidingItems().size() > 0)
    {
        for (QGraphicsItem *colliding_item : collision_box_right->collidingItems())
        {
            if (typeid(*colliding_item) == typeid(Mystery_Block) ||
                    typeid(*colliding_item) == typeid(Pipe_Block) ||
                    typeid(*colliding_item) == typeid(Floor_Block) ||
                    typeid(*colliding_item) == typeid(Brick_Block))
            {
                direction = -1;
            }
        }
    }

    if (collision_box_left->collidingItems().size() > 0)
    {
        for (QGraphicsItem *colliding_item : collision_box_left->collidingItems())
        {
            if (typeid(*colliding_item) == typeid(Mystery_Block) ||
                    typeid(*colliding_item) == typeid(Pipe_Block) ||
                    typeid(*colliding_item) == typeid(Floor_Block) ||
                    typeid(*colliding_item) == typeid(Brick_Block))
            {
                direction = 1;
            }
        }
    }

    setPos(x() + (0.5 * direction), y() + velY);
}

void Mushroom_Object::initial_animation()
{
    if((initial_y - 32) == y() - 8)
    {
        timer->stop();
        movement = true;
    }
    else {
        setPos(x(), y()-4);
    }

}
