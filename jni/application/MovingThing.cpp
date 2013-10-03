#include "MovingThing.h"

MovingThing::MovingThing(float x, float y, float width, float height, float depth) : Thing(x, y, width, height, depth) {
  type |= MOVINGTHING;
  grounded = false;
  moving = false;
  staticed = false;
  holding = NULL;
  life = 100;
  texture = "me";
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
  if (velocity.x > 0) {
    flipped = false;
  } else if (velocity.x < 0) {
    flipped = true;
  }
}

void MovingThing::give(MovingThing * thing) {
  if (thing != NULL) {
    holding = thing;
  }
}

MovingThing * MovingThing::take() {
  MovingThing * result = holding;
  holding = NULL;
  return result;
}

void MovingThing::handleCollision(Thing * thing, int direction) {
  if (direction & Constants::DOWN) {
    grounded = true;
    setPos(getPos().x, thing->getTopAt(getPos().x));
  } else {
    if (direction & Constants::LEFT) {
      //setPos(getPos().x-getVelocity().x, getPos().y);
      setPos(thing->getRight()+getSize().x/2, getPos().y);
    } else if (direction & Constants::RIGHT) {
      //setPos(getPos().x-getVelocity().x, getPos().y);
      setPos(thing->getLeft()-getSize().x/2, getPos().y);
    }
    /*if (direction & (Constants::LEFT | Constants::RIGHT) && thing->type & MOVINGTHING) {
      Vector2f vel = ((MovingThing*)thing)->getVelocity();
      thing->setPos(thing->getPos().x-vel.x, thing->getPos().y-vel.y);
    }*/
  }
}

void MovingThing::damage(Point2f pos, int points) {
  life -= points;
  //cout<<this<<" ow! "<<life<<endl;
  if (life <= 0) {
    die();
  }
}

void MovingThing::die() {
  staticed = true;
}
  
void MovingThing::move() {
  this->x += velocity.x;
  this->y += velocity.y;
}
  
void MovingThing::render(Point2f pos, Vector2f size) const {
  Thing::render(String(texture), pos, size);
}