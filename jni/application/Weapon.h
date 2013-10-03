#ifndef WEAPON_H
#define WEAPON_H

#include <zenilib.h>
#include "MovingThing.h"

using namespace std;
using namespace Zeni;

enum weaponName { MELEE, BOWLING, SWORD, GUN, MONEY, BEER };

class Weapon : public MovingThing {
  public:
    Weapon(Point2f pos, float width, float height, float depth, int life, int damage);
    
    virtual void handleCollision(Thing * thing, int direction);
    MovingThing * take();
    void die();
    bool heavy;
    weaponName name;
  protected:
    int damagePoints;
    
};

class Melee : public Weapon {
public:
  Melee(Point2f pos, float depth, int damage);
  void handleCollision(Thing * thing, int direction);
};

class Bowling : public Weapon {
public:
  Bowling(Point2f pos, float depth);
  void handleCollision(Thing * thing, int direction);
  void render(Point2f pos, Vector2f size) const;
};

class Gun : public Weapon {
public:
  Gun(Point2f pos, float depth);
  void handleCollision(Thing * thing, int direction);
  int bullets;
};

#endif // HEADER FILE
