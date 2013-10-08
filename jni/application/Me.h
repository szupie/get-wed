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
    Me(float x=0, float y=0, float size=0, float depth=1);
  
    void attack();
    Point2f getAttackPoint();
    Point2f getThrowPoint();
    void action(MovingThing* thing);
    
    void handleCollision(Thing * thing, int direction);
  
    void doThrow();
    void chargeThrow(int frame);
    void releaseCharge();
    void throwIt();
  
    void damage(Point2f pos, int points);
    void move();
  
    // Attacks
    void smack(int frame);
    void slash(int frame);
    void shoot(int frame);
  
    int walkingAccel;
    float currentFrame;
    ThingsList * renderList;
    int dirtiness;
    
    void render(Point2f pos, Vector2f size) const;
  
  private:
    void (Me::*currentAction)(int);
    int actionCounter;
    float throwPower;
  
};

#endif // HEADER FILE
