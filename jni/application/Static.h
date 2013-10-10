#ifndef STATIC_H
#define STATIC_H

#include <zenilib.h>
#include "Thing.h"

using namespace std;
using namespace Zeni;

class Static : public Thing {
  public:
    Static(float x=0, float y=0, float width=0, float height=0, float depth=1);
    
    void setTexture(String texture);
    
    void render(Point2f pos, Vector2f size) const;
    
  private:
    String texture;
};

class Ground : public Static {
  public:
    Ground(float x=0, float y=0, float width=0, float height=0, float depth=1);
};

class Wall : public Static {
public:
  Wall(float x=0, float y=0, float width=0, float height=0, float depth=1);
};

#endif // HEADER FILE
