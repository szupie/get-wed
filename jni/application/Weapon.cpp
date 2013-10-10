#include "Weapon.h"

Weapon::Weapon(Point2f pos, float width, float height, float depth, int life, int damage) : MovingThing(pos.x, pos.y, width, height, depth) {
  type |= WEAPON;
  heavy = false;
  perishable = false;
  friction = 0.7;
  damagePoints = damage;
  maxSpeed = 100;
  this->life = life;
  //cout<<width<<" and "<<height<<", life is "<<this->life<<endl;
}

void Weapon::handleCollision(Thing * thing, int direction) {
  //cout<<this<<" vs. "<<thing<<" (direction is "<<direction<<endl;
  if (direction != 0) {
    MovingThing * theThing = (MovingThing*)thing;
    if (theThing->type & MOVINGTHING) {
      theThing->damage(getPos(), damagePoints*velocity.magnitude());
      theThing->accelerate(Vector2f(0, -1));
      if (perishable) {
        this->damage(getPos(), damagePoints*velocity.magnitude());
      }
    }
  }
}

MovingThing * Weapon::take() {
  held = true;
  grounded = false;
  return this;
}

void Weapon::boom() {
  if (perishable) {
    deletable = true;
    setPos(-9999999, -9999999);
  }
}


Melee::Melee(Point2f pos, float width, float height, float depth, int damage) : Weapon(pos, width, height, depth, 0, damage) {
  name = MELEE;
  noRender = true;
  texture = "green"; //<<DEBUGGING!
  perishable = true;
}

void Melee::handleCollision(Thing * thing, int direction) {
  Weapon::handleCollision(thing, direction);
  deletable = true;
}

Bullet::Bullet(Point2f pos, float depth) : Weapon(pos, 10, 5, depth, 1, 100) {
  //name = BULLET;
  //renderSize = Vector2f(5, 2.5f);
  texture = "bullet";
  perishable = true;
}


Bowling::Bowling(Point2f pos, float depth) : Weapon(pos, 35, 35, depth, 500, 20) {
  name = BOWLING;
  texture = "bowling";
  friction = 0.98;
  heavy = true;
}

void Bowling::handleCollision(Thing * thing, int direction) {
  MovingThing::handleCollision(thing, direction);
  if (direction != 0) {
    MovingThing * theThing = (MovingThing*)thing;
    if (theThing->type & MOVINGTHING && velocity.magnitude()>1) {
      theThing->damage(getPos(), damagePoints*velocity.magnitude());
      //this->damage(getPos(), damagePoints); // Indestructable
    }
  }
}

void Bowling::render(Point2f pos, Vector2f size) const {
  float rotation = -x/50;
  Thing::render(String(texture), pos, size, rotation, Color());
}


Gun::Gun(Point2f pos, float depth) : Weapon(pos, 26, 13, depth, 500, 20) {
  name = GUN;
  texture = "gun";
  bullets = 6;
}

void Gun::handleCollision(Thing * thing, int direction) {
  MovingThing::handleCollision(thing, direction);
  Weapon::handleCollision(thing, direction);
}

void Gun::render(Point2f pos, Vector2f size) const {
  float rotation = -x/50;
  Thing::render(String(texture), pos, size, rotation, Color());
}


Sword::Sword(Point2f pos, float depth) : Weapon(pos, 72, 18, depth, 500, 30) {
  name = SWORD;
  texture = "sword";
}

void Sword::handleCollision(Thing * thing, int direction) {
  MovingThing::handleCollision(thing, direction);
  Weapon::handleCollision(thing, direction);
}

void Sword::render(Point2f pos, Vector2f size) const {
  float rotation = -x/100;
  Thing::render(String(texture), pos, size, rotation, Color());
}


Money::Money(Point2f pos, float depth, int value) : Weapon(pos, 30, 15, depth, value, 0) {
  name = MONEY;
  texture = "money";
}

void Money::handleCollision(Thing * thing, int direction) {
  MovingThing::handleCollision(thing, direction);
}

MovingThing * Money::take() {
  deletable = true;
  return this;
}


Bleach::Bleach(Point2f pos, float depth) : Weapon(pos, 40, 40, depth, 500, 0) {
  name = BLEACH;
  texture = "bleach";
}

void Bleach::handleCollision(Thing * thing, int direction) {
  MovingThing::handleCollision(thing, direction);
}

MovingThing * Bleach::take() {
  deletable = true;
  return this;
}
