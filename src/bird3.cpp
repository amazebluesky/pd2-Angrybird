#include "bird3.h"

bird3::bird3(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene) : Bird(x,y,radius,timer,pixmap,world,scene)
{

}
void bird3::skill()
{
    g_body->SetLinearVelocity(b2Vec2(float (g_body->GetLinearVelocity().x)*100,float (g_body->GetLinearVelocity().y)*0));
}
