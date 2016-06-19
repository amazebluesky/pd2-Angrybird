#include "bird2.h"

bird2::bird2(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene) : Bird(x,y,radius,timer,pixmap,world,scene)
{

}
void bird2::skill()
{
    g_body->SetLinearVelocity(b2Vec2(float (g_body->GetLinearVelocity().x)*0,float (-abs(g_body->GetLinearVelocity().y)*100)));
}
