#include "Thing.h"

Thing::Thing(float x, float y, float width, float height, float depth) {
  type = THING;
  name = NOWEAPON;
  held = false;
  flipped = false;
  setPos(x, y);
  setSize(width, height);
  renderSize = Vector2f(width, height);
  this->depth = depth;
  noRender = false;
  deletable = false;
  setSlope(0, 1);
}
  
Thing::~Thing() {}

Vector2f Thing::getSize() const {
  return Vector2f(width, height);
}

void Thing::setSize(float width, float height) {
  this->width = width;
  this->height = height;
}

void Thing::setSlope(float slope, float intercept) {
  this->slope = slope;
  this->intercept = intercept;
}

Vector2f Thing::getNormal() {
  return Vector2f(-slope, 1).normalize();
}

Point2f Thing::getPos() const {
  return Point2f(x, y);
}

void Thing::setPos(float x, float y) {
  this->x = x;
  this->y = y;
}

float Thing::getDepth() {
  return depth;
}

float Thing::getTopAt(float x) {
  float relX = x - getPos().x;
  return getPos().y - height - (slope*(relX-intercept));
}

float Thing::getRight() {
  return getPos().x + width/2;
}

float Thing::getBottom() {
  return getPos().y;
}

float Thing::getLeft() {
  return getPos().x - width/2;
}

void Thing::render(const String &texture, Point2f pos, Vector2f size, float rotation, Color tint) const {
  if (!noRender) {
    render_image(texture, 
                 Point2f(pos.x-(renderSize.x/2), pos.y-renderSize.y), 
                 Point2f(pos.x+(renderSize.x/2), pos.y), 
                 rotation,
                 1,
                 Point2f(pos.x, pos.y-size.y/2),
                 flipped, 
                 tint);
  }
}

void Thing::render(const String &texture, Point2f pos, Vector2f size) const {
  render(texture, pos, size, 0, Color(1, depth, depth, depth));//0.2f+depth*0.6f, 0.4f+depth*0.6f, 0.4f+depth*0.6f));
}
