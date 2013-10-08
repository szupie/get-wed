#include "Person.h"

Person::Person(float x, float y, float width, float height, float depth) : MovingThing(x, y, width, height, depth) {
  type |= PERSON;
  maxSpeed = 3;
  friction = 0.7;
  walkingAccel = 1.0f;
  goalReached = false;
  follower = false;
}

void Person::accelerate(Vector2f accel) {
  velocity += accel;
  // max land speed
  if (grounded && abs(velocity.x) > maxSpeed) velocity.x = abs(velocity.x)/velocity.x*maxSpeed;
  if (velocity.x >= 1) {
    flipped = false;
  } else if (velocity.x <= -1) {
    flipped = true;
  }
}

void Person::handleCollision(Thing * thing, int direction) {
  MovingThing::handleCollision(thing, direction);
  if (direction & (Constants::LEFT | Constants::RIGHT)) {
    goalReached = true;
  }
}

void Person::walkTo(float interval, float x) {
  moving = false;
  if (grounded) {
    float diff = x - this->x;
    float speed = abs(diff)/diff*interval*walkingAccel;
    if (diff > 0) {
      flipped = false;
    } else if (diff < 0) {
      flipped = true;
    }
    //cout<<diff<<(abs(diff) > this->width*1.3 && keepWalking)<<(abs(diff) > this->width*5)<<endl;
    if (((abs(diff) > this->width*1.3 && !goalReached) || // stop when close enough
        abs(diff) > this->width*3) && // start when far enough
        abs(diff) < this->width*10) { // Do not chase when too far
      //velocity.x = speed;
      accelerate(Vector2f(speed, 0));
      moving = true;
      goalReached = false;
    } else {
      goalReached = true;
    }
  }
}

void Person::damage(Point2f pos, int points) {
  MovingThing::damage(pos, points);
  cout<<this<<" hit for "<<points<<", now "<<life<<endl;
  if (!staticed) {
    if (life <= 0) {
      boom();
      depth -= 0.2;
    }
  }
}

void Person::boom() {
  MovingThing::boom();
  currentFrame = 0;
}

void Person::move() {
  stringstream num;
  if (!staticed && isSatisfied()) {
    staticed = true;
    depth -= 0.2;
  }
  if (!staticed) {
    MovingThing::move();
    if (!moving) {
      currentFrame += 1;
      num << abs(int(currentFrame/50)%3);
      texture = textureBase + string("rest") + num.str();
    } else {
      currentFrame = x/10.0;
      if (currentFrame > 1200) currentFrame -= 1200;
      else if (currentFrame < 0) currentFrame += 1200;
      num << abs(int(currentFrame)%10);
      texture = textureBase + string("walk") + num.str();
    }
  } else {
    currentFrame++;
    if (currentFrame < 40 && life <= 0) {
      num << abs(int(currentFrame/10)%4);
      texture = textureBase + string("die") + deathAnim + num.str();
    }
  }
}

void Person::render(Point2f pos, Vector2f size) const {
  Color tint;
  if (!staticed) {
    tint = Color(1.0f, 1.0f, life/100.0f, life/100.0f);
  } else {
    tint = Color(1.0f, 0.5f, 0.5f, 0.5f);
  }
  Thing::render(String(texture), pos, size, 0, tint);
}
