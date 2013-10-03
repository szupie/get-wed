#include "Me.h"

float ACCEL = 8;
float MAXSPEED = 5;

Me::Me(float x, float y, float width, float height, float depth) : MovingThing(x, y, width, height, depth) {
  type |= ME;
  maxSpeed = MAXSPEED;
  walkingAccel = ACCEL;
  friction = 0.7;
  throwPower = 2;
  currentAction = NULL;
  currentFrame = 0;
  frames.push_back("mewalk1");
  frames.push_back("mewalk2");
  frames.push_back("mewalk3");
  frames.push_back("mewalk4");
  frames.push_back("mewalk5");
  frames.push_back("mewalk6");
  frames.push_back("mewalk7");
  frames.push_back("mewalk8");
  frames.push_back("mewalk9");
  frames.push_back("mewalk10");
  texture = frames[int(currentFrame)];
}

void Me::attack(ThingsList * renderList) {
  this->renderList = renderList;
  if (currentAction == NULL) {
    currentAction = &Me::smack;
    actionCounter = 0;
    GameCamera::targetZoom = 0.5;
  }
}

void Me::smack(int frame) {
  int speed = 7;
  if (frame == 3*speed) {
    Melee * smackPoint = new Melee(getAttackPoint(), getDepth(), 20);
    renderList->append(smackPoint);
  } else if (frame/speed > 3) {
    currentAction = NULL;
    GameCamera::setZoomOutView();
    return;
  }
  char num[2];
  sprintf(num, "mewalk%d", (frame/speed)+6);
  texture = num;
}

Point2f Me::getAttackPoint() {
  float horiz = getRight()+5;
  if (flipped) horiz = getLeft()-5;
  return Point2f(horiz, y-height*.75); // 5px offset
}

Point2f Me::getThrowPoint() {
  float horiz = getRight()+holding->getSize().x/2+5;
  if (flipped) horiz = getLeft()-holding->getSize().x/2-5;
  float vert = y-height*.75;
  if (holding->type & WEAPON && ((Weapon*)holding)->name == BOWLING) {
    vert = y-5; // 5px offset for teh lulz?
  }
  return Point2f(horiz, vert); // 5px offset
}

void Me::action(MovingThing * thing) {
  if (holding == NULL) give(thing->take());
  if (holding != NULL && holding->type & WEAPON) {
    if (((Weapon*)holding)->heavy) {
      maxSpeed = MAXSPEED/2;
      walkingAccel = ACCEL/2;
      cout<<"SLOWED"<<maxSpeed<<endl;
    }
  }
  cout<<"holding "<<holding<<endl;
}

void Me::chargeThrow(ThingsList * renderList) {
  if (holding != NULL) {
    this->renderList = renderList;
    throwPower *= 1.02;
    cout<<"power at "<<throwPower<<endl;
    GameCamera::targetZoom = 0.4;
    if (throwPower >= 20) {
      throwIt();
    }
  }
}

void Me::throwIt() {
  if (holding != NULL) {
    holding->setPos(getThrowPoint().x, getThrowPoint().y);
    if (flipped) throwPower *= -1;
    holding->accelerate(Vector2f(throwPower, 0));
    cout<<"throwing at "<<throwPower<<endl;
    cout<<"its speed is "<<holding->getVelocity().x<<endl;
    holding->held = false;
    renderList->append(holding);
    holding = NULL;
    throwPower = 1;
    maxSpeed = MAXSPEED;
    walkingAccel = ACCEL;
    cout<<"NORMAL"<<maxSpeed<<endl;
    GameCamera::setZoomOutView();
  }
}

void Me::damage(Point2f pos, int points) {
  // no damage
}

void Me::move() {
  MovingThing::move();
  
  currentFrame = currentFrame+(velocity.x/40.0);
  if (currentFrame > 10) currentFrame -= 10;
  else if (currentFrame < 0) currentFrame += 10;
  
  if (velocity.magnitude() < 1) {
    texture = "merest0";
  } else {
    texture = frames[int(currentFrame)%10];
  }
  
  if (currentAction != NULL) {
    (*this.*currentAction)(actionCounter);
    actionCounter++;
  }
}

