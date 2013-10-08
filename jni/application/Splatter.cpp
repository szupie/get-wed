#include "Splatter.h"

Splatter::Splatter(Point2f pos, float size, float depth) : MovingThing(pos.x, pos.y, size, size, depth) {
  type |= SPLATTER;
  life = 0;
  texture = "splatter00";
  stringstream num;
  num << rand()%3;
  randKind = num.str();
}

void Splatter::boom() {
  const int framesPerSprite = 5;
  const int sprites = 5;
  if (dieFrame >= sprites*framesPerSprite) {
    deletable = true;
  } else {
    stringstream num;
    num << dieFrame/framesPerSprite;
    texture = string("splatter") + randKind + num.str();
    dieFrame++;
  }
}