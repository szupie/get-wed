#include "MovingThing.h"

MovingThing::MovingThing(float x, float y, float width, float height, float depth) : Thing(x, y, width, height, depth) {
  type |= MOVINGTHING;
  grounded = false;
  moving = false;
  money = 0;
  staticed = false;
  holding = NULL;
  dieFrame = 0;
  life = 100;
  texture = "blank";
}
  
MovingThing::~MovingThing() {}
  
void MovingThing::setVelocity(Vector2f velocity) {
  this->velocity = velocity;
}
  
Vector2f MovingThing::getVelocity() {
  return velocity;
}

void MovingThing::applyFriction() {
  if (!moving) {
    velocity.x *= friction;
  }
}

void MovingThing::accelerate(Vector2f accel) {
  velocity += accel;
  // max land speed
  if (grounded && abs(velocity.x) > maxSpeed) velocity.x = abs(velocity.x)/velocity.x*maxSpeed;
  if (velocity.x >= 0.5f) {
    flipped = false;
  } else if (velocity.x <= -0.5f) {
    flipped = true;
  }
}

void MovingThing::give(MovingThing * thing) {
  if (thing != NULL) {
    if (thing->name == MONEY) {
      money += thing->life;
    } else if (thing->name != BLEACH) {
      holding = thing;
    }
  }
}

MovingThing * MovingThing::take() {
  MovingThing * result = holding;
  holding = NULL;
  return result;
}

void MovingThing::handleCollision(Thing * thing, int direction) {
  if (type & SPLATTER || thing->type & SPLATTER) return; // Ignore splatters
  if (direction & Constants::DOWN) {
    grounded = true;
    setPos(getPos().x, thing->getTopAt(getPos().x));
    if (!moving) {
      accelerate(thing->getNormal()*Constants::gravity*0.5); // sliding part of normal force
    }
  } else if (direction & Constants::UP) {
    setPos(getPos().x, thing->getBottom()+getSize().y);
    setVelocity(Vector2f(getVelocity().x, 0));
  } else {
    if (direction & (Constants::LEFT | Constants::RIGHT)) {
      if (this->type & PERSON) {
        accelerate(Vector2f(-getVelocity().x/*-getFace()*.9f*/, 0));
      } else {
        accelerate(Vector2f(-getVelocity().x*0.1f, 0));
      }
    }
    if (direction & Constants::LEFT) {
      //setPos(getPos().x-getVelocity().x, getPos().y);
      //setPos(thing->getRight()+getSize().x/2, getPos().y);)
      if (thing->type & STATIC) {
        setPos(thing->getRight()+getSize().x/2, getPos().y);
      } else {
        thing->setPos(getLeft()-thing->getSize().x/2, thing->getPos().y);
      }
    } else if (direction & Constants::RIGHT) {
      //setPos(getPos().x-getVelocity().x, getPos().y);
      //setPos(thing->getLeft()-getSize().x/2, getPos().y);
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
}

void MovingThing::damage(Point2f pos, int points) {
  life -= points;
}

void MovingThing::boom() {
  staticed = true;
}

int MovingThing::getFace() {
  if (flipped) {
    return -1;
  }
  return 1;
}

int MovingThing::holds() {
  if (holding != NULL) {
    return holding->name;
  }
  return 0;
}
  
void MovingThing::move() {
  this->x += velocity.x;
  this->y += velocity.y;
  if (life <= 0) {
    boom();
  }
}
  
void MovingThing::render(Point2f pos, Vector2f size) const {
  Thing::render(String(texture), pos, size);
}
