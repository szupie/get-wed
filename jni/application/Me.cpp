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
}

void Me::attack() {
  this->renderList = renderList;
  if (currentAction == NULL) {
    actionCounter = 0;
    if (holding == NULL) {
      currentAction = &Me::smack;
      GameCamera::targetZoom = 0.5;
    } else {
      // What's the attack?
      Weapon * weapon = (Weapon*)holding;
      if (weapon->name == GUN) {
        currentAction = &Me::shoot;
      }
    }
  }
}

void Me::smack(int frame) {
  int totalFrames = 28;
  int sprites = 4;
  if (frame == 3*totalFrames/sprites) {
    Melee * smackPoint = new Melee(getAttackPoint(), getDepth(), 20);
    // damage = speed*dp, so x1
    smackPoint->accelerate(Vector2f(getFace(),0));
    renderList->append(smackPoint);
  } else if (frame >= totalFrames) {
    currentAction = NULL;
    GameCamera::setZoomOutView();
    return;
  }
  char num[7];
  sprintf(num, "mewalk%d", (frame*sprites/totalFrames)+6);
  texture = num;
}

void Me::shoot(int frame) {
  int totalFrames = 7;
  int sprites = 1;
  if (frame == 1*totalFrames/sprites) {
    if (((Gun*)holding)->bullets > 0) {
      Bullet * bullet = new Bullet(getAttackPoint(), getDepth());
      bullet->accelerate(Vector2f(getFace()*50, 0));
      renderList->append(bullet);
      ((Gun*)holding)->bullets--;
    }
  } else if (frame >= totalFrames) {
    currentAction = NULL;
    return;
  }
  char num[7];
  sprintf(num, "mewalk%d", (frame*sprites/totalFrames)+3);
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
    vert = y-16; // matches animation
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

void Me::doThrow() {
  if (currentAction == NULL && holding != NULL) {
    actionCounter = 0;
    GameCamera::targetZoom = 0.4;
    currentAction = &Me::chargeThrow;
  }
}

void Me::chargeThrow(int frame) {
  if (holding != NULL && ((Weapon*)holding)->name == BOWLING) {
    int framesPerSprite = 5;
    if (frame == 4*framesPerSprite) {
      frame = 3*framesPerSprite;
    } else if (frame >= 7*framesPerSprite) {
      throwIt();
      return;
    }
    char num[13];
    cout<<frame<<" and "<<int(frame/framesPerSprite)<<endl;
    if (sprintf(num, "bowlingthrow%d", int(frame/framesPerSprite))) {
      cout<<"SUCCESS!"<<num<<endl;
      texture = num;
    } else {
      cout<<"BOO "<<int(frame/framesPerSprite)<<endl;
    }
    throwPower *= 1.02;
    cout<<"power at "<<throwPower<<endl;
    if (throwPower >= 20) {
      actionCounter = 4*5+1;
    }
  } else if (holding == NULL) {
    currentAction = NULL;
  }
}

void Me::releaseCharge() {
  if (holding != NULL) {
    if (((Weapon*)holding)->name == BOWLING) {
      if (actionCounter <= 4*5) actionCounter = 4*5+1;
    } else {
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
    currentAction = NULL;
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
  char num[7];
  
  if (velocity.magnitude() < 1) {
    currentFrame += 1;
    sprintf(num, "merest%d", int(currentFrame/50)%4);
    texture = num;
  } else {
    currentFrame += velocity.x/40.0;
    if (currentFrame > 10) currentFrame -= 10;
    else if (currentFrame < 0) currentFrame += 10;
    sprintf(num, "mewalk%d", int(currentFrame)%10);
    texture = num;
  }
  
  if (currentAction != NULL) {
    (*this.*currentAction)(actionCounter);
    actionCounter++;
  }
}

