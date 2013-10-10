#ifndef ME_H
#define ME_H

#include <zenilib.h>
#include "MovingThing.h"
#include "Bridesmaid.h"
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
    void give(MovingThing * thing);
  
    void say(string text);
    void insult(int type);
  
    // Attacks
    void smack(int frame);
    void slash(int frame);
    void shoot(int frame);
  
    int walkingAccel;
    float currentFrame;
    ThingsList * renderList;
    int dirtiness;
    Text * myText;
    Chronometer<Time> talkTimer;
    
    void render(Point2f pos, Vector2f size) const;
  
  private:
    void (Me::*currentAction)(int);
    int actionCounter;
    float throwPower;
  
};

class Checkpoint {
public:
  Checkpoint(float top, float right, float bottom, float left) {
    this->top = top;
    this->right = right;
    this->bottom = bottom;
    this->left = left;
  };
  bool check(Point2f pos) {
    return (pos.y > top && pos.y < bottom && 
            pos.x < right && pos.x > left);
  }
  float top;
  float right;
  float bottom;
  float left;
};

#endif // HEADER FILE
