#ifndef PERSON_H
#define PERSON_H

#include <zenilib.h>
#include <sstream>
#include "MovingThing.h"

using namespace std;
using namespace Zeni;

class Person : public MovingThing {
  public:
    Person(float x=0, float y=0, float width=0, float height=0, float depth=1);
    void accelerate(Vector2f accel);
    void handleCollision(Thing * thing, int direction);
    void walkTo(float interval, float x);
    void damage(Point2f pos, int points);
    void boom();
    void move();
    bool follower;
  
    void render(Point2f pos, Vector2f size) const;
  
  protected:
    string textureBase;
    float currentFrame;
    string deathAnim;
    virtual bool isSatisfied() = 0;
  
  private:
    float maxSpeed;
    float walkingAccel;
    bool goalReached;
    
};

#endif // HEADER FILE
