#include "Weapon.h"

Weapon::Weapon(Point2f pos, float width, float height, float depth, int life, int damage) : MovingThing(pos.x, pos.y, width, height, depth) {
  type |= WEAPON;
  heavy = false;
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
      theThing->damage(getPos(), damagePoints);
      this->damage(getPos(), damagePoints);
    }
  }
}

MovingThing * Weapon::take() {
  held = true;
  grounded = false;
  return this;
}

void Weapon::die() {
  deletable = true;
  setPos(-9999999, -9999999);
  cout<<"You can delete "<<this<<" now"<<endl;
}


Melee::Melee(Point2f pos, float depth, int damage) : Weapon(pos, 10, 10, depth, damage, damage) {
  name = MELEE;
  noRender = true;
}

void Melee::handleCollision(Thing * thing, int direction) {
  Weapon::handleCollision(thing, direction);
  deletable = true;
}


Bowling::Bowling(Point2f pos, float depth) : Weapon(pos, 50, 50, depth, 20, 500) {
  name = BOWLING;
  texture = "bowling";
  friction = 0.95;
  heavy = true;
}

void Bowling::handleCollision(Thing * thing, int direction) {
  if (direction & Constants::DOWN) {
    grounded = true;
    setPos(getPos().x, thing->getTopAt(getPos().x));
  } else {
    if (direction & Constants::LEFT) {
      //setPos(getPos().x-getVelocity().x, getPos().y);
      if (thing->type & STATIC) {
        setPos(thing->getRight()+getSize().x/2, getPos().y);
      } else {
        thing->setPos(getLeft()-thing->getSize().x/2, thing->getPos().y);
      }
    } else if (direction & Constants::RIGHT) {
      //setPos(getPos().x-getVelocity().x, getPos().y);
      if (thing->type & STATIC) {
        setPos(thing->getLeft()-getSize().x/2, getPos().y);
      } else {
        thing->setPos(getRight()+thing->getSize().x/2, thing->getPos().y);
      }
    }
    /*if (direction & (Constants::LEFT | Constants::RIGHT) && thing->type & MOVINGTHING) {
     Vector2f vel = ((MovingThing*)thing)->getVelocity();
     thing->setPos(thing->getPos().x-vel.x, thing->getPos().y-vel.y);
     }*/
  }
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
  Thing::render(String(texture), pos, size, rotation);
}


Gun::Gun(Point2f pos, float depth) : Weapon(pos, 10, 10, depth, 100, 500) {
  name = GUN;
  bullets = 6;
}

void Gun::handleCollision(Thing * thing, int direction) {
  Weapon::handleCollision(thing, direction);
  deletable = true;
}