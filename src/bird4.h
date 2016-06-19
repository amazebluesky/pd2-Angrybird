#ifndef BIRD4_H
#define BIRD4_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>
#include <bird.h>

#define BIRD_DENSITY 10.0f
#define BIRD_FRICTION 0.1f
#define BIRD_RESTITUTION 0.5f

class bird4 : public Bird
{
public:
    bird4(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    virtual void skill();
};

#endif // BIRD4_H
