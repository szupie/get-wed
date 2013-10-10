#ifndef MOVINGTHING_H
#define MOVINGTHING_H

#include <zenilib.h>
#include "Thing.h"
#include "Constants.h"

using namespace std;
using namespace Zeni;

class MovingThing : public Thing {
  public:
    MovingThing(float x=0, float y=0, float width=0, float height=0, float depth=1);
  
    virtual ~MovingThing();
    
    void setVelocity(Vector2f velocity);
    Vector2f getVelocity();
  
    void applyFriction();
    
    virtual void accelerate(Vector2f accel);
  
    virtual void give(MovingThing * thing);
    
    virtual MovingThing * take();
    
    virtual void handleCollision(Thing * thing, int direction);
  
    virtual void damage(Point2f pos, int points);
  
    virtual void boom();
  
    int getFace();
    int holds();
  
    virtual void move();
  
    void render(Point2f pos, Vector2f size) const;
  
    bool grounded;
    bool moving;
    bool staticed;
    int life;
    int money;
    
  protected:
    Vector2f velocity;
    float maxSpeed;
    float friction;
    string texture;
    int dieFrame;
    MovingThing * holding;
};

#endif // HEADER FILE
