#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <zenilib.h>
#include "ThingsList.h"
#include "GameCamera.h"
#include "Me.h"
#include "Bridesmaid.h"
#include "Static.h"
#include "Splatter.h"
#include "Text.h"

using namespace std;
using namespace Zeni;
    
enum Direction { NONE, DOWN=1, LEFT=2, UP=4, RIGHT=8, IN=16 };

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
    string checkCheckpoints();
    void render();
    void onUpDown();
    void onShiftRelease();
    void onActionDown();
    void onSpaceDown();
  
    void makeLevel(int lvl);
    
    Me * player;
    bool isLeftDown;
    bool isRightDown;
    bool isShiftDown;
    bool isUpReleased;
    bool isActionReleased;
    bool isSpaceReleased;
    Chronometer<Time> gameTimer;
    Chronometer<Time> weddingTimer;
    float timePassed;
    ThingsList renderList;
    vector<Text *> textList;
    
    string lastCheckpoint;
    map<string, Checkpoint *> checkpoints;
    string * timeDisplay;
  
    void on_push();
    void on_pop();
    void on_key(const SDL_KeyboardEvent &event);
    void on_joy_axis(const SDL_JoyAxisEvent &event);
    
    map<Thing *, string> thingsDebug;
    int homelessKilled;
    int bmKilled;
};

#endif // HEADER FILE
