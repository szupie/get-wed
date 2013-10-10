#ifndef WEAPON_H
#define WEAPON_H

#include <zenilib.h>
#include "MovingThing.h"

using namespace std;
using namespace Zeni;

class Weapon : public MovingThing {
  public:
    Weapon(Point2f pos, float width, float height, float depth, int life, int damage);
    
    virtual void handleCollision(Thing * thing, int direction);
    virtual MovingThing * take();
    void boom();
    bool heavy;
    int damagePoints;
  protected:
    bool perishable;
    
};

class Melee : public Weapon {
public:
  Melee(Point2f pos, float width, float height, float depth, int damage);
  void handleCollision(Thing * thing, int direction);
};

class Bullet : public Weapon {
public:
  Bullet(Point2f pos, float depth);
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
  void render(Point2f pos, Vector2f size) const;
  int bullets;
};

class Sword : public Weapon {
public:
  Sword(Point2f pos, float depth);
  void handleCollision(Thing * thing, int direction);
  void render(Point2f pos, Vector2f size) const;
};

class Money : public Weapon {
public:
  Money(Point2f pos, float depth, int value);
  void handleCollision(Thing * thing, int direction);
  MovingThing * take();
};

class Bleach : public Weapon {
public:
  Bleach(Point2f pos, float depth);
  void handleCollision(Thing * thing, int direction);
  MovingThing * take();
};

#endif // HEADER FILE
