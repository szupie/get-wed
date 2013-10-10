#ifndef TEXT_H
#define TEXT_H

#include <zenilib.h>

using namespace std;
using namespace Zeni;

class Text {
  public:
    Text(float x, float y, float depth, string text="", string font="ingame");
  
    ~Text();
  
    void render();
    void render(Point2f pos);
  
    string * text;
    float depth;
    float x;
    float y;
    string font;
    JUSTIFY justify;
    
};

#endif // HEADER FILE
