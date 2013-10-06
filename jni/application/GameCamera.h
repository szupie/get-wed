#ifndef GAMECAMERA_H
#define GAMECAMERA_H

#include <zenilib.h>
#include "Thing.h"

using namespace std;
using namespace Zeni;

class GameCamera {
  public:
    static void setFocus(Thing * object);
    static void setZoomOutView();
    static void set46View();
    static pair<Point2f, Point2f> getView();
    static Point2f getCenter();
    static void pan();
    
    static void renderThing(Thing * thing);
    static float relativeSize;
    static Point2f location;
    static float targetZoom;
    static float offset;
    static float targetOffset;
  
  private:
    static Thing * focus;

};

#endif // HEADER FILE
