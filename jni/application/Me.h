#ifndef ME_H
#define ME_H

#include <zenilib.h>
#include "MovingThing.h"
#include "Weapon.h"
#include "ThingsList.h"
#include "GameCamera.h"

using namespace std;
using namespace Zeni;

class Me : public MovingThing {
  public:
    Me(float x=0, float y=0, float width=0, float height=0, float depth=1);
  
    void attack(ThingsList * renderList);
    void smack(int frame);
    Point2f getAttackPoint();
    Point2f getThrowPoint();
    void action(MovingThing* thing);
  
    void chargeThrow(ThingsList * renderList);
    void throwIt();
  
    void damage(Point2f pos, int points);
    void move();

    int walkingAccel;
    vector<string> frames;
    float currentFrame;
  
  private:
    void (Me::*currentAction)(int);
    int actionCounter;
    float throwPower;
    ThingsList * renderList;
  
};

#endif // HEADER FILE
