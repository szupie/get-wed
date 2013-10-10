#ifndef PERSON_H
#define PERSON_H

#include <zenilib.h>
#include <sstream>
#include "MovingThing.h"
#include "ThingsList.h"
#include "Weapon.h"
#include "Text.h"

using namespace std;
using namespace Zeni;

class Person : public MovingThing {
  public:
    Person(float x=0, float y=0, float width=0, float height=0, float depth=1);
    static ThingsList * renderList;
    void accelerate(Vector2f accel);
    void handleCollision(Thing * thing, int direction);
    void lookTo(float interval, Point2f pos);
    void damage(Point2f pos, int points);
    void boom();
    void move();
    void say(string text);
    
    bool follower;
    bool inSight;
    bool justSeen;
    Weapon * stash;
    Text * myText;
    bool talking;
    Chronometer<Time> talkTimer;
  
    string greeting;
    bool greeted;
    string parting;
  
    static vector<Text *> * textList;
    int textOffset;
  
    void render(Point2f pos, Vector2f size) const;
  
    float currentFrame;
  protected:
    string textureBase;
    string deathAnim;
    virtual bool isSatisfied() = 0;
  
  private:
    float maxSpeed;
    float walkingAccel;
    bool goalReached;
    
};

#endif // HEADER FILE
