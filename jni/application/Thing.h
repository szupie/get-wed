#ifndef THING_H
#define THING_H

#include <zenilib.h>

using namespace std;
using namespace Zeni;

enum ThingType { THING=1, STATIC=1<<1, MOVINGTHING=1<<2, PERSON=1<<3, ME=1<<4, WEAPON=1<<5 };

class Thing {
  public:
    Thing(float x=0, float y=0, float width=0, float height=0, float depth=1);
  
    virtual ~Thing();
  
    virtual void render(Point2f pos, Vector2f size) const = 0;
    
    Vector2f getSize() const;
    void setSize(float width, float height);
    
    void setSlope(float slope, float intercept);
    Vector2f getNormal();
    
    Point2f getPos() const;
    void setPos(float x, float y);
    
    float getDepth();
    
    float getTopAt(float x);
    float getRight();
    float getBottom();
    float getLeft();
  
    Vector2f renderSize;
    
    bool deletable;
    bool held;
  
    bool flipped;
    int type;

  protected:
    float x;
    float y;
    float width;
    float height;
    float depth;
    float slope;
    float intercept;
    bool noRender;
  
    void render(const String &texture, Point2f pos, Vector2f size, float rotation) const;
    void render(const String &texture, Point2f pos, Vector2f size) const;
    
};

#endif // HEADER FILE
