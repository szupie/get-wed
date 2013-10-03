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
    static pair<Point2f, Point2f> get46();
    static Point2f getCenter();
    static void pan();
    
    static void renderThing(Thing * thing);
    static float relativeSize;
    static Point2f location;
    static float targetZoom;
  
  private:
    static Thing * focus;

};

#endif // HEADER FILE
