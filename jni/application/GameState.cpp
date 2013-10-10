#include "GameState.h"

float GRAVITY = 0.3f;

GameState::GameState() {
  player = new Me(0, 0, 100, 1);
  
  // Initialise
  timePassed = 0.0f;
  isLeftDown = false;
  isRightDown = false;
  isActionReleased = true;
  isUpReleased = true;
  isSpaceReleased = true;
  homelessKilled = 0;
  bmKilled = 0;
  Bridesmaid::initFeelings();
  
  renderList.append(player);
  Person::renderList = &renderList;
  Person::textList = &textList;
  player->renderList = &renderList;
  textList.push_back(player->myText);
  timeDisplay = new string();
  
  GameCamera::location = player->getPos();
  GameCamera::setFocus(player);
  GameCamera::set46View();
  GameCamera::setZoomOutView();
  
  makeLevel(0);
  //player->setPos(8800+1550, 525);
  //makeLevel(4);
  //set_pausable(true);
  //weddingTimer.start();

  gameTimer.start();
}
  
GameState::~GameState() {
  while (!renderList.empty()) {
    renderList.pop();
  }
  checkpoints.clear();
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
        GameCamera::targetZoom = 0.4;
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
  if (obj1->getBottom() >= obj2->getTopAt(obj1->getPos().x) &&
      obj1->getBottom() <= obj2->getBottom() &&
      obj1->getPos().x > obj2->getLeft() &&
      obj1->getPos().x < obj2->getRight()) {
    hitDir |= IN;
  }
  if (moveDirection.y >= 0 && // Going down or staying
      // 5px buffer to assist stair declimbing
      obj1->getBottom()+5 >= obj2->getTopAt(obj1->getPos().x) &&
      obj1->getBottom() <= obj2->getTopAt(obj1->getPos().x)+obj1->getSize().y &&
      obj1->getPos().x > obj2->getLeft() &&
      obj1->getPos().x < obj2->getRight()) {
    hitDir = hitDir | DOWN;
  } else if (moveDirection.y < 0 && // Going up
        obj1->getTopAt(obj1->getPos().x) <= obj2->getBottom() &&
        obj1->getTopAt(obj1->getPos().x) >= obj2->getBottom()-obj1->getSize().y &&
        obj1->getPos().x > obj2->getLeft() &&
        obj1->getPos().x < obj2->getRight()) {
    hitDir = hitDir | UP;
  } else
  if (moveDirection.x < 0 && // Going left
      obj1->getLeft() <= obj2->getRight() &&
      obj1->getLeft() >= obj2->getLeft() &&
      // 30px buffer
      obj1->getBottom() > obj2->getTopAt(obj1->getPos().x)+20 &&
      obj1->getTopAt(obj1->getPos().x) < obj2->getBottom()) {
    hitDir = hitDir | LEFT;
  } else if (moveDirection.x > 0 && // Going right
             obj1->getRight() >= obj2->getLeft() &&
             obj1->getRight() <= obj2->getRight() &&
             // 30px buffer
             obj1->getBottom() > obj2->getTopAt(obj1->getPos().x)+20 &&
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
      if (obj1->getDepth() == 1) {
        obj1->grounded = false;
        for (int j=0; j<renderList.length(); j++) {
          Thing * obj2 = renderList[j];
          if (obj2 && obj2->getDepth() == obj1->getDepth() && obj1 != obj2 && !(obj2->type & WEAPON)) {
            int hitDirection = checkCollision(obj1, obj2);
            if (hitDirection != 0 && obj1->type & WEAPON && obj2->type & PERSON) {
              float splatterSize = ((Weapon*)obj1)->damagePoints*2;
              Splatter * splatter = new Splatter(obj1->getPos(), splatterSize, obj1->getDepth());
              splatter->setPos(obj1->getPos().x-obj1->getFace()*splatter->getSize().x/4, obj1->getPos().y+splatter->getSize().y/2);
              splatter->setVelocity(Vector2f(-1*obj1->getFace(), -1));
              splatters.append(splatter);
            }
            //if ((obj1->type | obj2->type) & WEAPON) cout<<obj1<<" plus "<<obj2<<" this and ";
            obj1->handleCollision(obj2, hitDirection);
            //if (obj2->type & MOVINGTHING) {
            //  hitDirection ^= LEFT | RIGHT; // flip horiz direction
            //  ((MovingThing*)obj2)->handleCollision(obj1, hitDirection);
            //}
            //if (hitDirection != 0) cout<<"going in "<<hitDirection<<" hit is "<<thingsDebug[obj1]<<" and "<<thingsDebug[obj2]<<"; obj1type: "<<obj1->type<<", ojb2type: "<<obj2->type<<endl;
            //cout<<obj1<<" vs. "<<obj2<<endl;
          } else if (obj2->getDepth() > 1) { // reach end of depth
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
  bool outOfOrder = false;
  for (int i=renderList.length()-1; i>=0; i--) {
    if (i < renderList.length()) {
      if (renderList[i]->deletable) {
        //cout<<"deleting "<<renderList[i]<<endl;
        delete renderList.remove(i);
      } else if (renderList[i]->held) {
        renderList.remove(i);
      }
      if (i > 0 && CompareThings::compare(renderList[i], renderList[i-1])) {
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
    Person * peep = dynamic_cast<Person*>(renderList[i]);
    //cout<<renderList[i]->type<<(renderList[i]->type & PERSON)<<endl;
    if (peep) {
      if (peep->type & PERSON && !peep->staticed) {
        peep->lookTo(interval, player->getPos());
      }
      if (peep->inSight && peep->life <= 0 && peep->currentFrame <= 1) { // just died
        if (peep->type & HOBO) {
          homelessKilled++;
        } else if (peep->type & BRIDESMAID) {
          bmKilled++;
        }
        player->insult(peep->type);
      }
    }
  }
  
  string textBubble = checkCheckpoints();
  if (textBubble != "xx") player->say(textBubble);
  
  applyPhysics();
}

void GameState::onUpDown() {
  if (player->grounded && !(player->holds() == BOWLING) ) {
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
  get_Video().set_clear_Color(Color(1, .004f, .678f, .933f));
  GameCamera::pan();
  get_Video().set_2d(GameCamera::getView(), true);
  
  for (int i=0; i<renderList.length(); i++) {
    GameCamera::renderThing(renderList[i]);
  }
  
  for (uint i=0; i<textList.size(); i++) {
    GameCamera::renderText(textList[i]);
  }
  
  get_Video().set_2d(make_pair(Point2f(0.0f, 0.0f), Point2f(1280.0f, 800.0f)), true);
  get_Fonts()["HUD"].render_text("Cash: $" + ulltoa(player->money), Point2f(1280.0f, 800.0f-40.0f), Color(0.5f,1,1,1), ZENI_RIGHT);
  get_Fonts()["HUD"].render_text("Clean Dress: " + ulltoa(max(100-player->dirtiness/10, 0)) + "%", Point2f(0.0f, 800.0f-40.0f), Color());
  
  //get_Fonts()["tiny"].render_text("FPS: " + ulltoa(get_Game().get_fps()), Point2f(0.0f, 800.0f-16.0f), Color());
  //get_Fonts()["time"].render_text(String(timeDisplay), Point2f(640.0f, 800.0f-40.0f), Color(0.5f,1,1,1), ZENI_CENTER);
}
