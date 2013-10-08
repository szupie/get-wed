#include "GameState.h"

float GRAVITY = 0.3f;

GameState::GameState() {
  player = new Me(100, 1000, 100, 1);
  Bridesmaid * dude = new Bridesmaid(700, 1000, 100, 1);
  Hobo * dude2 = new Hobo(900, 1000, 100, 1);
  Bridesmaid * dude3 = new Bridesmaid(950, 1000, 100, 1);
  Bridesmaid * dude4 = new Bridesmaid(1000, 1000, 100, 1);
  renderList.append(dude2);
  renderList.append(dude4);
  renderList.append(dude3);
  Hobo * hbo1 = new Hobo(-600, 1000, 100, 1);
  Hobo * hbo2 = new Hobo(-800, 1000, 100, 1);
  Hobo * hbo3 = new Hobo(-1000, 1000, 100, 1);
  renderList.append(hbo1);
  renderList.append(hbo2);
  renderList.append(hbo3);
  
  Static * bg = new Static(100, 1024, 20480, 1024, 0.5);
  Static * ground = new Static(-500, 1100, 20480, 100, 1);
  Static * ground2 = new Static(-550, 1100, 20480, 100, 0.8);
  Static * ground3 = new Static(-550, 1100, 20480, 100, 0.7);
  Bowling * bowling = new Bowling(Point2f(-200, 1000), 1);
  Gun * gun = new Gun(Point2f(-300, 1000), 1);
  Sword * sword = new Sword(Point2f(-400, 1000), 1);
  Money * stacks = new Money(Point2f(-500, 1000), 1, 25);
  Static * newThing = new Static(-100,1000,100,50,1);
  Static * triangle = new Static(350,1000,200,100,1);
  Static * triangle2 = new Static(550,1000,200,100,1);
  Static * newThing2 = new Static(0,1000,20,250,1.2);
  bg->setTexture("blue");
  ground->setTexture("ground");
  ground2->setTexture("ground");
  ground3->setTexture("ground");
  newThing->setTexture("green");
  newThing2->setTexture("green");
  triangle->setTexture("triangle");
  triangle2->setTexture("triangleflip");
  triangle->setSlope(0.5, 100);
  triangle2->setSlope(-0.5, -100);
  player->renderList = &renderList;
  
  thingsDebug[player] = "Player";
  thingsDebug[ground] = "ground";
  thingsDebug[ground2] = "ground2";
  thingsDebug[bowling] = "bowling";
  thingsDebug[gun] = "Gun";
  thingsDebug[newThing] = "newThing";
  thingsDebug[newThing2] = "newThing2";
  thingsDebug[triangle] = "triangle1";
  thingsDebug[triangle2] = "triangle2";
  thingsDebug[bg] = "bg";
  thingsDebug[dude] = "dude";
  
  cout<<"Player is "<<player<<endl;
  cout<<"dude is "<<dude<<endl;
  cout<<"gun is "<<gun<<endl;
  cout<<"bg is "<<bg<<endl;
  cout<<"ground is "<<ground<<endl;
  cout<<"bowling is "<<bowling<<endl;
  cout<<"newThing is "<<newThing<<endl;
  cout<<"newThing2 is "<<newThing2<<endl;
  cout<<"triangle is "<<triangle<<endl;
  cout<<"triangle2 is "<<triangle2<<endl;
  
  renderList.append(player);
  renderList.append(bg);
  renderList.append(ground);
  renderList.append(ground2);
  renderList.append(ground3);
  renderList.append(bowling);
  renderList.append(gun);
  renderList.append(sword);
  renderList.append(stacks);
  renderList.append(triangle);
  renderList.append(triangle2);
  renderList.append(newThing);
  renderList.append(newThing2);
  renderList.append(dude);
  
  // Initialise
  timePassed = 0.0f;
  isLeftDown = false;
  isRightDown = false;
  isActionReleased = true;
  isUpReleased = true;
  isSpaceReleased = true;
  GameCamera::location = player->getPos();
  GameCamera::setFocus(player);
  GameCamera::set46View();
  GameCamera::setZoomOutView();
  set_pausable(true);

  gameTimer.start();
}
  
GameState::~GameState() {
  while (!renderList.empty()) {
    renderList.pop();
  }
}

void GameState::on_push() {
  //get_Window().mouse_grab(true);
  get_Window().mouse_hide(true);
  //get_Game().joy_mouse.enabled = false;
}

void GameState::on_pop() {
  //get_Window().mouse_grab(false);
  get_Window().mouse_hide(false);
  //get_Game().joy_mouse.enabled = true;
}

void GameState::on_joy_axis(const SDL_JoyAxisEvent &event) {
  cout<<"Action!"<<event.value<<endl;
  if ( ( event.value < -3200 ) || (event.value > 3200 ) ) {
    if( event.axis == 0) {
      isLeftDown = (event.value > 0);
      isRightDown = (event.value > 0);
    }
    
    if( event.axis == 1) {
      /* Up-Down movement code goes here */
    }
  }
}
  
void GameState::on_key(const SDL_KeyboardEvent &event) {
  switch(event.keysym.sym) {
    case SDLK_a:
    case SDLK_LEFT:
      isLeftDown = (event.type == SDL_KEYDOWN);
      break;
    case SDLK_RIGHT:
    case SDLK_d:
      isRightDown = (event.type == SDL_KEYDOWN);
      break;
    case SDLK_UP:
    case SDLK_w:
      if (!event.repeat && isUpReleased && event.type == SDL_KEYDOWN) {
        onUpDown();
      }
      if (event.type == SDL_KEYUP) {
        isUpReleased = true;
      }
      break;
    case SDLK_DOWN:
    case SDLK_s:
      if (!event.repeat && isActionReleased && event.type == SDL_KEYDOWN) {
        onActionDown();
        isActionReleased = false;
        GameCamera::targetZoom = 0.7;
      }
      if (event.type == SDL_KEYUP) {
        isActionReleased = true;
        GameCamera::setZoomOutView();
      }
      break;
    case SDLK_LSHIFT:
    case SDLK_RSHIFT:
      isShiftDown = (event.type == SDL_KEYDOWN);
      if (event.type == SDL_KEYUP) {
        onShiftRelease();
      }
      break;
    case SDLK_SPACE:
      if (!event.repeat && isSpaceReleased && event.type == SDL_KEYDOWN) {
        onSpaceDown();
        isSpaceReleased = false;
      }
      if (event.type == SDL_KEYUP) {
        isSpaceReleased = true;
      }
      break;
    default:
      Gamestate_Base::on_key(event); // Let Gamestate_Base handle it
      break;
  }
}

int GameState::checkCollision(MovingThing * obj1, Thing * obj2) {
  int hitDir = 0;
  Vector2f moveDirection = obj1->getVelocity();
  if (obj2->type & MOVINGTHING) {
    moveDirection -= ((MovingThing*)obj2)->getVelocity();
  }
  if (obj1->type & WEAPON && obj2->type & (PERSON | ME) && obj1->getVelocity().magnitude()<1) {
    return 0;
  }
  if (moveDirection.y >= 0 && // Going down or staying
      // 5px buffer to assist stair declimbing
      obj1->getBottom()+5 >= obj2->getTopAt(obj1->getPos().x) &&
      obj1->getBottom() <= obj2->getBottom() &&
      obj1->getPos().x > obj2->getLeft() &&
      obj1->getPos().x < obj2->getRight()) {
    hitDir = hitDir | DOWN;
  }
  if (moveDirection.x < 0 && // Going left
      obj1->getLeft() <= obj2->getRight() &&
      obj1->getLeft() >= obj2->getLeft() &&
      // Only check if hitting bottom 3/4
      obj1->getBottom() > obj2->getTopAt(obj1->getPos().x)+obj2->getSize().y*0.75 &&
      obj1->getTopAt(obj1->getPos().x) < obj2->getBottom()) {
    hitDir = hitDir | LEFT;
  } else if (moveDirection.x > 0 && // Going right
             obj1->getRight() >= obj2->getLeft() &&
             obj1->getRight() <= obj2->getRight() &&
             // Only check if hitting bottom half
             obj1->getBottom() > obj2->getTopAt(obj1->getPos().x)+obj2->getSize().y/2 &&
             obj1->getTopAt(obj1->getPos().x) < obj2->getBottom()) {
    hitDir = hitDir | RIGHT;
  }
  //cout<<thingsDebug[obj1]<<" and "<<thingsDebug[obj2]<<moveDirection.x<<" "<<hitDir<<endl;
  return hitDir;
}

void GameState::applyPhysics() {
  //cout<<endl;
  ThingsList splatters;
  for (int i=0; i<renderList.length(); i++) {
    MovingThing * obj1 = dynamic_cast<MovingThing*>(renderList[i]);
    //cout<<"checking "<<obj1<<endl;
    if (obj1 && !obj1->staticed) { // Is moving object
      //cout<<"checking "<<thingsDebug[obj1]<<endl;
      obj1->grounded = false;
      for (int j=0; j<renderList.length(); j++) {
        Thing * obj2 = renderList[j];
        if (obj2->getDepth() == obj1->getDepth() && obj1 != obj2 && !(obj2->type & WEAPON)) {
          int hitDirection = checkCollision(obj1, obj2);
          if (hitDirection != 0 && obj1->type & WEAPON && obj2->type & PERSON) {
            float splatterSize = ((Weapon*)obj1)->damagePoints*2;
            Splatter * splatter = new Splatter(obj1->getPos(), splatterSize, obj1->getDepth());
            splatter->setPos(obj1->getPos().x-obj1->getFace()*splatter->getSize().x/4, obj1->getPos().y+splatter->getSize().y/2);
            splatter->setVelocity(Vector2f(-1*obj1->getFace(), -1));
            splatters.append(splatter);
            cout<<"SPLAT size"<<splatterSize<<endl;
          }
          //if ((obj1->type | obj2->type) & WEAPON) cout<<obj1<<" plus "<<obj2<<" this and ";
          obj1->handleCollision(obj2, hitDirection);
          //if (obj2->type & MOVINGTHING) {
          //  hitDirection ^= LEFT | RIGHT; // flip horiz direction
          //  ((MovingThing*)obj2)->handleCollision(obj1, hitDirection);
          //}
          //if (hitDirection != 0) cout<<"going in "<<hitDirection<<" hit is "<<thingsDebug[obj1]<<" and "<<thingsDebug[obj2]<<"; obj1type: "<<obj1->type<<", ojb2type: "<<obj2->type<<endl;
          //cout<<obj1<<" vs. "<<obj2<<endl;
        } else if (obj2->getDepth() > obj1->getDepth()) { // reach end of depth
          break;
        }
      }
      
      if (obj1->grounded) {
        obj1->setVelocity(obj1->getVelocity().multiply_by(Vector2f(1, 0))); // Stop
        obj1->applyFriction();
      } else {
        obj1->accelerate(Vector2f(0, GRAVITY)); // Gravity
      }
    }
    
    if (obj1) obj1->move();
  }
  for (int i=0; i<splatters.length(); i++) {
    renderList.append(splatters[i]);
  }
}
  
void GameState::perform_logic() {
  const float interval = gameTimer.seconds() - timePassed;
  timePassed = gameTimer.seconds();
  
  //cout<<endl<<"Start of moment, interval is "<<interval<<endl;
  
  // Clean up
  int tempDepth = renderList[renderList.length()-1]->getDepth();
  bool outOfOrder = false;
  for (int i=renderList.length()-1; i>=0; i--) {
    if (i < renderList.length()) {
      if (renderList[i]->deletable) {
        //cout<<"deleting "<<renderList[i]<<endl;
        delete renderList.remove(i);
      } else if (renderList[i]->held) {
        renderList.remove(i);
      }
      if (tempDepth < renderList[i]->getDepth()) {
        outOfOrder = true;
      }
    }
  }
  if (outOfOrder) {
    renderList.reorder();
  }
  
  // Apply controls
  if (player->grounded) {
    int keyDirection = isLeftDown*-1 + isRightDown;
    player->moving = (keyDirection != 0); // isn't neutral
    if (player->moving) {
      player->accelerate(Vector2f(keyDirection*interval*player->walkingAccel, 0));
    }
  }
  if (isShiftDown) {
    player->doThrow();
  }
  
  // Apply AI
  for (int i=0; i<renderList.length(); i++) {
    Person * peep = (Person*)renderList[i];
    //cout<<renderList[i]->type<<(renderList[i]->type & PERSON)<<endl;
    if (peep->type & PERSON && peep->follower && !peep->staticed) {
      peep->walkTo(interval, player->getPos().x);
    }
  }
  
  applyPhysics();
}

void GameState::onUpDown() {
  if (player->grounded) {
    player->accelerate(Vector2f(0, -6)); // Jump!
  }
}

void GameState::onShiftRelease() {
  player->releaseCharge();
}

void GameState::onActionDown() {
  for (int i=0; i<renderList.length(); i++) {
    if (renderList[i]->getDepth() == player->getDepth() && renderList[i]->type & MOVINGTHING) {
      Vector2f distance = renderList[i]->getPos() - player->getPos();
      if (player->flipped) distance.x *= -1;
      if (distance.x > -player->getSize().x && distance.x < player->getSize().x*2) { // if within range of player
        player->action((MovingThing*)renderList[i]);
        cout<<"actioning "<<thingsDebug[renderList[i]]<<endl;
      }
    } else if (renderList[i]->getDepth() > player->getDepth()) {
      break;
    }
  }
}

void GameState::onSpaceDown() {
  player->attack();
}
  
void GameState::render() {
  //get_Video().set_clear_Color(Color(0, 255, 255, 255));
  GameCamera::pan();
  get_Video().set_2d(GameCamera::getView(), true);
  
  for (int i=0; i<renderList.length(); i++) {
    GameCamera::renderThing(renderList[i]);
  }
  
  get_Video().set_2d(make_pair(Point2f(0.0f, 0.0f), Point2f(1280.0f, 800.0f)), true);
  get_Fonts()["tiny"].render_text("FPS: " + ulltoa(get_Game().get_fps()), Point2f(0.0f, 800.0f-64.0f), Color());
  get_Fonts()["HUD"].render_text("Cash: $" + ulltoa(player->money), Point2f(1280.0f, 0.0f), Color(), ZENI_RIGHT);
  get_Fonts()["HUD"].render_text("Clean Dress: " + ulltoa(100-player->dirtiness/10) + "%", Point2f(0.0f, 0.0f), Color());
}
