#include "Person.h"

Person::Person(float x, float y, float width, float height, float depth) : MovingThing(x, y, width, height, depth) {
  type |= PERSON;
  maxSpeed = 3;
  friction = 0.7;
  walkingAccel = 10.0f;
  goalReached = false;
}

void Person::walkTo(float interval, float x) {
  moving = false;
  if (grounded) {
    float diff = x - this->x;
    float speed = min(abs(diff)*interval*walkingAccel, maxSpeed);
    if (diff > 0) {
      flipped = false;
    } else if (diff < 0) {
      flipped = true;
    }
    //cout<<diff<<(abs(diff) > this->width*1.3 && keepWalking)<<(abs(diff) > this->width*5)<<endl;
    if (((abs(diff) > this->width*1.3 && !goalReached) || // stop when close enough
        abs(diff) > this->width*3) && // start when far enough
        abs(diff) < this->width*10) { // Do not chase when too far
      if (diff<0) {
        speed *= -1;
      }
      velocity.x = speed;
      moving = true;
      goalReached = false;
    } else {
      goalReached = true;
    }
  }
}

void Person::damage(Point2f pos, int points) {
  life -= points;
  //cout<<this<<" ow! "<<life<<endl;
  if (!staticed) {
    if (life <= 0) {
      die();
    }
  } else {
    depth -= 0.2;
  }
}

void Person::die() {
  MovingThing::die();
  texture = "medead";
}
