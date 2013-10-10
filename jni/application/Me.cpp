#include "Me.h"

float ACCEL = 8;
float MAXSPEED = 4;

Me::Me(float x, float y, float size, float depth) : MovingThing(x, y, size*.32f, size*.94f, depth) {
  type |= ME;
  renderSize = Vector2f(size, size);
  maxSpeed = MAXSPEED;
  walkingAccel = ACCEL;
  friction = 0.7;
  throwPower = 2;
  dirtiness = 0;
  currentAction = NULL;
  currentFrame = 0;
  myText = new Text(x, y, depth);
}

void Me::attack() {
  if (currentAction == NULL) {
    actionCounter = 0;
    if (holding == NULL) {
      currentAction = &Me::smack;
      GameCamera::targetZoom = 0.4;
    } else {
      // What's the attack?
      Weapon * weapon = (Weapon*)holding;
      if (weapon->name == GUN) {
        if (((Gun*)holding)->bullets > 0) {
          currentAction = &Me::shoot;
          if (!flipped)
            GameCamera::targetOffset = 0.1;
          else
            GameCamera::targetOffset = 0.9;
        } else {
          currentAction = &Me::smack;
        }
      }
      if (weapon->name == SWORD) {
        currentAction = &Me::slash;
      }
      GameCamera::targetZoom = 0.4;
    }
  }
}

void Me::smack(int frame) {
  int totalFrames = 20;
  int sprites = 4;
  if (holding != NULL && ((Weapon*)holding)->name == GUN) {
    sprites = 5;
  }
  if (frame == 3*totalFrames/sprites) {
    Melee * smackPoint = new Melee(getAttackPoint(), 20, 20, getDepth(), 20);
    // damage = speed*dp, so x1
    smackPoint->accelerate(Vector2f(getFace(),0));
    renderList->append(smackPoint);
  } else if (frame >= totalFrames) {
    currentAction = NULL;
    GameCamera::setZoomOutView();
    GameCamera::set46View();
    return;
  }
  char num[1];
  sprintf(num, "%d", frame*sprites/totalFrames);
  if (holding != NULL && ((Weapon*)holding)->name == GUN) {
    texture = string("gunsmack") + num;
  } else {
    texture = string("mesmack") + num;
  }
}

void Me::slash(int frame) {
  int totalFrames = 21;
  int sprites = 3;
  if (frame == 1*totalFrames/sprites) {
    Vector2f area = ((Weapon*)holding)->getSize();
    Melee * slashPoint = new Melee(getAttackPoint()+Vector2f(0, area.y), area.x, area.y*2, getDepth(), 50);
    // damage = speed*dp, so x1
    slashPoint->accelerate(Vector2f(getFace(),0));
    renderList->append(slashPoint);
  } else if (frame >= totalFrames) {
    currentAction = NULL;
    this->renderSize = Vector2f(100, 100);
    GameCamera::setZoomOutView();
    GameCamera::set46View();
    return;
  }
  char num[1];
  sprintf(num, "%d", frame*sprites/totalFrames);
  texture = string("swordhit") + num;
  this->renderSize = Vector2f(200, 100);
}

void Me::shoot(int frame) {
  int totalFrames = 20;
  int sprites = 5;
  if (frame == 0*totalFrames/sprites) {
    if (((Gun*)holding)->bullets > 0) {
      Bullet * bullet = new Bullet(getAttackPoint(), getDepth());
      bullet->accelerate(Vector2f(getFace()*30, 0));
      renderList->append(bullet);
      ((Gun*)holding)->bullets--;
    }
  } else if (frame >= totalFrames) {
    currentAction = NULL;
    GameCamera::setZoomOutView();
    GameCamera::set46View();
    return;
  }
  char num[1];
  sprintf(num, "%d", frame*sprites/totalFrames);
  texture = string("gunfire") + num;
}

Point2f Me::getAttackPoint() {
  float horiz = getRight()+width/2;
  if (flipped) horiz = getLeft()-width/2;
  float vert = y-height*.68;
  if (holding != NULL && ((Weapon*)holding)->name == GUN) {
    vert = y-height*.63; // matches animation
  }
  return Point2f(horiz, vert); // 5px offset
}

Point2f Me::getThrowPoint() {
  float horiz = getRight()+width/2;
  if (flipped) horiz = getLeft()-width/2;
  float vert = y-height*.75;
  if (holding != NULL && ((Weapon*)holding)->name == BOWLING) {
    vert = y-height*.16; // matches animation
  }
  return Point2f(horiz, vert); // 5px offset
}

void Me::action(MovingThing * thing) {
  if (thing->type & HOBO && money > 0) {
    int howMuch = min(money, 5);
    thing->money += howMuch;
    money -= howMuch;
  }
  if (thing->type & BRIDESMAID && !((Bridesmaid*)thing)->talking) {
    ((Bridesmaid*)thing)->talking = true;
    ((Bridesmaid*)thing)->talkTimer.reset();
    cout<<((Bridesmaid*)thing)->talkTimer.seconds()<<endl;
    ((Bridesmaid*)thing)->talkTimer.start();
  }
  if (holding == NULL) give(thing->take());
  if (holding != NULL && holding->type & WEAPON) {
    if (((Weapon*)holding)->heavy) {
      maxSpeed = MAXSPEED/2;
      walkingAccel = ACCEL/2;
    }
  }
}

void Me::handleCollision(Thing * thing, int direction) {
  MovingThing::handleCollision(thing, direction);
  if (direction != 0 && thing->type & SPLATTER) {
    if (dirtiness == 0) {
      say("Ugh, I've got blood\nall over my dress!\nI can't get married\nin a bloody dress!");
    }
    dirtiness++;
  }
}

void Me::doThrow() {
  if (currentAction == NULL && holding != NULL) {
    actionCounter = 0;
    GameCamera::targetZoom = 0.4;
    if (!flipped)
      GameCamera::targetOffset = 0.1;
    else
      GameCamera::targetOffset = 0.9;
    currentAction = &Me::chargeThrow;
  }
}

void Me::chargeThrow(int frame) {
  const int framesPerSprite = 5;
  int holdingFrame = 3;
  int totalFrames = 4;
  if (((Weapon*)holding)->name == BOWLING) {
    holdingFrame = 4;
    totalFrames = 7;
  }
  if (holding != NULL) {
    throwPower *= 1.02;
    if (throwPower >= 15 && frame <= 100) {
      actionCounter = 100;
    }

    if (frame == holdingFrame*framesPerSprite) {
      actionCounter = (holdingFrame-1)*framesPerSprite;
      frame = (holdingFrame-1)*framesPerSprite;
    } else if (frame>=100) {
      frame = frame-100+holdingFrame*framesPerSprite;
    }
    if (frame >= totalFrames*framesPerSprite) {
      throwIt();
      return;
    }
    char num[1];
    sprintf(num, "%d", int(frame/framesPerSprite));
    if (((Weapon*)holding)->name == BOWLING) {
      texture = string("bowlingthrow") + num;
    } else if (((Weapon*)holding)->name == GUN) {
      texture = string("gunthrow") + num;
    } else if (((Weapon*)holding)->name == SWORD) {
      texture = string("swordthrow") + num;
    }
  } else if (holding == NULL) {
    currentAction = NULL;
  }
}

void Me::releaseCharge() {
  if (holding != NULL) {
    if (actionCounter < 100) actionCounter = 100;
  }
}

void Me::throwIt() {
  if (holding != NULL) {
    holding->setPos(getThrowPoint().x, getThrowPoint().y);
    if (flipped) throwPower *= -1;
    holding->accelerate(Vector2f(throwPower, 0));
    holding->held = false;
    renderList->append(holding);
    currentAction = NULL;
    holding = NULL;
    throwPower = 1;
    maxSpeed = MAXSPEED;
    walkingAccel = ACCEL;
    GameCamera::setZoomOutView();
    GameCamera::set46View();
  }
}

void Me::damage(Point2f pos, int points) {
  // no damage
}

void Me::give(MovingThing * thing) {
  MovingThing::give(thing);
  if (thing != NULL && thing->name == BLEACH) {
    dirtiness = 0;
    say("I love the feeling of bleach\n on my sensitive skin.");
  }
}

void Me::move() {
  MovingThing::move();
  char num[1];
  if (velocity.magnitude() < 1) {
    currentFrame += 1;
    if (holding != NULL && ((Weapon*)holding)->name == GUN) {
      sprintf(num, "%d", int(currentFrame)%1);
      texture = string("gunrest") + num;
    } else if (holding != NULL && ((Weapon*)holding)->name == BOWLING) {
      sprintf(num, "%d", int(currentFrame)%1);
      texture = string("bowlingrest") + num;
    } else if (holding != NULL && ((Weapon*)holding)->name == SWORD) {
      sprintf(num, "%d", int(currentFrame)%1);
      texture = string("swordrest") + num;
    } else {
      sprintf(num, "%d", int(currentFrame/50)%4);
      texture = string("merest") + num;
    }
  } else {
    currentFrame += velocity.x/30.0;
    if (currentFrame > 1200) currentFrame -= 1200;
    else if (currentFrame < 0) currentFrame += 1200;
    if (holding != NULL && ((Weapon*)holding)->name == GUN) {
      sprintf(num, "%d", int(currentFrame/3)%4);
      texture = string("gunwalk") + num;
    } else if (holding != NULL && ((Weapon*)holding)->name == BOWLING) {
      sprintf(num, "%d", int(currentFrame)%4);
      texture = string("bowlingwalk") + num;
    } else if (holding != NULL && ((Weapon*)holding)->name == SWORD) {
      sprintf(num, "%d", int(currentFrame/30)%4);
      texture = string("swordwalk") + num;
    } else {
      sprintf(num, "%d", int(currentFrame)%10);
      texture = string("mewalk") + num;
    }
  }
  
  if (currentAction != NULL) {
    (*this.*currentAction)(actionCounter);
    actionCounter++;
  }
}

void Me::say(string text) {
  talkTimer.reset();
  talkTimer.start();
  *myText->text = text;
}

void Me::insult(int type) {
  int lol = rand()%10;
  if (type & BRIDESMAID) {
    switch (lol) {
      case 0:
        say("You're ugly!");
        break;
      case 1:
        say("Your bangs look\nhorrible anyway!");
        break;
      case 2:
        say("You're fat!");
        break;
      case 3:
        say("We're not friends.");
        break;
      case 4:
        say("I don't care.");
        break;
      case 5:
        say("Leave me alone.");
        break;
      case 6:
        say("Why won't you die?");
        break;
      case 7:
        say("I love the way you die.");
        break;
      case 8:
        say("Today's the wrong day!");
        break;
      case 9:
        say("Shh.\nThat's it.\nJust step into the light.");
        break;
        
      default:
        say("Go away!");
        break;
    } 
  } else if (type & HOBO) {
      switch (lol) {
        case 0:
          say("Homeless people are gross.");
          break;
        case 1:
          say("Get away,\nyou dirty hobo!");
          break;
        case 2:
          say("Don't touch me!");
          break;
        case 3:
          say("Get a job!");
          break;
        case 4:
          say("While I understand the system of\noppression that people of your\nsocioeconomic status face,\nI'm not giving you my money.");
          break;
        case 5:
          say("Go home.");
          break;
        case 6:
          say("His family is\ngoing to miss him.");
          break;
        case 7:
          say("I hope I didn't\nget any diseases.");
          break;
        case 8:
          say("Wooo!");
          break;
        case 9:
          say("I am enjoying \nthe cold-blooded murder\nof innocents.");
          break;
          
        default:
          say("Go away!");
          break;
      }
  }
}

void Me::render(Point2f pos, Vector2f size) const {
  Color tint = Color(1.0f, 1.0f, 1.0f-(dirtiness/1000.0f), 1.0f-(dirtiness/1000.0f));
  Thing::render(String(texture), pos, size, 0, tint);
  myText->x = x;
  myText->y = y-height*2;
  if (talkTimer.seconds() > 5) {
    //talkTimer.stop();
    *myText->text = "";
  }
}

