#ifndef PERSON_H
#define PERSON_H

#include <zenilib.h>
#include "MovingThing.h"

using namespace std;
using namespace Zeni;

class Person : public MovingThing {
  public:
    Person(float x=0, float y=0, float width=0, float height=0, float depth=1);
    void walkTo(float interval, float x);
    void damage(Point2f pos, int points);
    void die();
  
  private:
    float maxSpeed;
    float walkingAccel;
    bool goalReached;
    
};

#endif // HEADER FILE
