#ifndef SPLATTER_H
#define SPLATTER_H

#include <zenilib.h>
#include <sstream>
#include "Me.h"

using namespace std;
using namespace Zeni;



class Splatter : public MovingThing {
public:
  Splatter(Point2f pos, float size, float depth);
  void boom();
  string randKind;
};

#endif // HEADER FILE
