#ifndef ENEMY_H
#define ENEMY_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

#define ENEMY_DENSITY 50.0f
#define ENEMY_FRICTION 0.1f
#define ENEMY_RESTITUTION 0.5f

class enemy : public GameItem
{
public:
    enemy(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    bool get();
};


#endif // ENEMY_H
