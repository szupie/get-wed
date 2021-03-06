/* This file is part of the Zenipex Library (zenilib).
 * Copyleft (C) 2011 Mitchell Keith Bloch (bazald).
 *
 * This source file is simply under the public domain.
 */

#include <zenilib.h>
#include "GameState.h"
#include "Me.h"
#include "Static.h"

#if defined(_DEBUG) && defined(_WINDOWS)
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

using namespace std;
using namespace Zeni;

class Instructions_State : public Widget_Gamestate {
  Instructions_State(const Instructions_State &);
  Instructions_State operator=(const Instructions_State &);

  public:
    Instructions_State()
      : Widget_Gamestate(make_pair(Point2f(0.0f, 0.0f), Point2f(800.0f, 600.0f)))
    {
    }

  private:
    void on_key(const SDL_KeyboardEvent &event) {
      if(event.keysym.sym == SDLK_ESCAPE && event.state == SDL_PRESSED)
        get_Game().pop_state();
    }

    void render() {
      Widget_Gamestate::render();

      Zeni::Font &fr = get_Fonts()["HUD"];

      fr.render_text("LEFT and RIGHT to move\n"
                     "UP to jump\n"
                     "DOWN to interact with environment\n"
                     "SPACE to attack\n"
                     "SHIFT to throw object",
                     Point2f(400.0f, 200.0f - 0.5f * fr.get_text_height()),
                     get_Colors()["title_text"],
                     ZENI_CENTER);
    }
};

class Bootstrap {
  class Gamestate_One_Initializer : public Gamestate_Zero_Initializer {
    virtual Gamestate_Base * operator()() {
      Window::set_title("Get Wed");

      //get_Joysticks();
      get_Video();
      get_Textures();
      get_Fonts();
      get_Sounds();
      //get_Game().joy_mouse.enabled = true;

      return new Title_State<GameState, Instructions_State>("GET WED!");
    }
  } m_goi;

  public:
    Bootstrap() {
      g_gzi = &m_goi;
    }
} g_bootstrap;

int main(int argc, char **argv) {
  return zenilib_main(argc, argv);
}
