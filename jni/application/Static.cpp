#include "Static.h"

Static::Static(float x, float y, float width, float height, float depth) : Thing(x, y, width, height, depth) {
  type |= STATIC;
  this->texture = "default";
}

void Static::setTexture(String texture) {
  this->texture = texture;
}
  
void Static::render(Point2f pos, Vector2f size) const {
  Thing::render(this->texture, pos, size);
}


Ground::Ground(float x, float y, float width, float height, float depth) : Static(x, y, width, height, depth) {
  setTexture("ground");
}

Wall::Wall(float x, float y, float width, float height, float depth) : Static(x, y, width, height, depth) {
  setTexture("ground");
}
