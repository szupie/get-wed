#include "Person.h"

ThingsList * Person::renderList;
vector<Text *> * Person::textList;

Person::Person(float x, float y, float width, float height, float depth) : MovingThing(x, y, width, height, depth) {
  type |= PERSON;
  maxSpeed = 3;
  friction = 0.7;
  walkingAccel = 1.0f;
  stash = NULL;
  goalReached = false;
  follower = false;
  talking = false;
  greeted = false;
  myText = new Text(x, y, depth);
  textList->push_back(myText);
  textOffset = 0;//25-(rand()%50);//26 + rand()%26);
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

void Person::lookTo(float interval, Point2f pos) {
  Vector2f distance = getPos()-pos;
  if (distance.magnitude() < this->width*8 && abs(distance.y) < this->height ) {
    if (!inSight) {
      justSeen = true;
      greeted = false;
    } else {
      justSeen = false;
    }
    inSight = true;
    if (!greeted && distance.magnitude() < this->width*1.5) {
      say(greeting);
      greeted = true;
    }
    if (follower) {
      moving = false;
      if (grounded) {
        float diff = pos.x - this->x;
        float speed = abs(diff)/diff*interval*walkingAccel;
        if (diff > 0) {
          flipped = false;
        } else if (diff < 0) {
          flipped = true;
        }
        //cout<<diff<<(abs(diff) > this->width*1.3 && keepWalking)<<(abs(diff) > this->width*5)<<endl;
        if (((abs(diff) > this->width*1.3 && !goalReached) || // stop when close enough
             abs(diff) > this->width*3)) { // start when far enough
          //velocity.x = speed;
          accelerate(Vector2f(speed, 0));
          moving = true;
          goalReached = false;
        } else {
          goalReached = true;
        }
      }
    }
  } else {
    inSight = false;
  }
}

void Person::damage(Point2f pos, int points) {
  MovingThing::damage(pos, points);
  *myText->text = "";
  if (!staticed) {
    if (life <= 0) {
      boom();
      depth -= 0.001;
    }
  }
}

void Person::boom() {
  MovingThing::boom();
  currentFrame = 0;
  delete stash;
  stash = NULL;
  *myText->text = "";
}

void Person::move() {
  stringstream num;
  if (!staticed && isSatisfied()) {
    staticed = true;
    texture = textureBase + string("rest0");
    if (stash != NULL) {
      stash->setPos(x, y);
      renderList->append(stash);
    }
    depth -= 0.001;
  }
  if (!staticed) {
    MovingThing::move();
    if (!moving) {
      num << abs(int(currentFrame/50)%3);
      texture = textureBase + string("rest") + num.str();
    } else {
      currentFrame = x/10.0;
      num << abs(int(currentFrame)%10);
      texture = textureBase + string("walk") + num.str();
    }
    currentFrame += 1;
    if (currentFrame > 1200) currentFrame -= 1200;
    else if (currentFrame < 0) currentFrame += 1200;
  } else {
    currentFrame++;
    if (currentFrame < 40 && life <= 0) {
      num << abs(int(currentFrame/10)%4);
      texture = textureBase + string("die") + deathAnim + num.str();
    }
  }
  if (talkTimer.seconds() > 5 && !talking) {
    talkTimer.stop();
    *myText->text = "";
  }
}

void Person::say(string text) {
  talkTimer.reset();
  talkTimer.start();
  *myText->text = text;
}

void Person::render(Point2f pos, Vector2f size) const {
  Color tint;
  if (!staticed) {
    tint = Color(1.0f, 1.0f, life/100.0f, life/100.0f);
  } else {
    tint = Color(1.0f, 0.5f, 0.5f, 0.5f);
  }
  Thing::render(String(texture), pos, size, 0, tint);
  myText->x = x;
  myText->y = y-renderSize.y*2+textOffset;
}
