#include "Static.h"

Static::Static(float x, float y, float width, float height, float depth) : Thing(x, y, width, height, depth) {
  type |= STATIC;
  cout<<"this static is "<<this<<" type is "<<type<<endl;
  this->texture = "default";
}

void Static::setTexture(String texture) {
  this->texture = texture;
}
  
void Static::render(Point2f pos, Vector2f size) const {
  Thing::render(this->texture, pos, size);
}

