#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <zenilib.h>
#include "ThingsList.h"
#include "GameCamera.h"
#include "Me.h"
#include "Person.h"
#include "Static.h"

using namespace std;
using namespace Zeni;
    
enum Direction { NONE, DOWN=1, LEFT=2, UP=4, RIGHT=8 };

class GameState : public Gamestate_Base {
  public:
    GameState(const GameState &);
    GameState operator=(const GameState &);
    GameState();
    ~GameState();

  private:
    int checkCollision(MovingThing * obj1, Thing * obj2);
    void applyPhysics();
    void perform_logic();
    void render();
    void onUpDown();
    void onShiftRelease();
    void onActionDown();
    void onSpaceDown();
    
    Me * player;
    bool isLeftDown;
    bool isRightDown;
    bool isShiftDown;
    bool isUpReleased;
    bool isActionReleased;
    bool isSpaceReleased;
    Chronometer<Time> gameTimer;
    float timePassed;
    ThingsList renderList;
    list<Person *> aiList;
  
    void on_push();
    void on_pop();
    void on_key(const SDL_KeyboardEvent &event);
    void on_joy_axis(const SDL_JoyAxisEvent &event);
    
    map<Thing *, string> thingsDebug;
};

#endif // HEADER FILE
