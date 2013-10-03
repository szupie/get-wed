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
    
    void accelerate(Vector2f accel);
  
    void give(MovingThing * thing);
    
    virtual MovingThing * take();
    
    virtual void handleCollision(Thing * thing, int direction);
  
    virtual void damage(Point2f pos, int points);
  
    virtual void die();
  
    int getFace();
  
    virtual void move();
  
    void render(Point2f pos, Vector2f size) const;
  
    bool grounded;
    bool moving;
    bool staticed;
    
  protected:
    Vector2f velocity;
    float maxSpeed;
    float friction;
    int life;
    string texture;
    MovingThing * holding;
};

#endif // HEADER FILE
