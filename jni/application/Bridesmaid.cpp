#include "Bridesmaid.h"

Bridesmaid::Bridesmaid(float x, float y, float size, float depth) : Person(x, y, size*.32f, size*.94f, depth) {
  type |= BRIDESMAID;
  renderSize = Vector2f(size, size);
  follower = true;
  textureBase = "bm";
  stringstream num;
  num << rand()%2;
  deathAnim = num.str();
}

bool Bridesmaid::isSatisfied() {
  return false;
}

Hobo::Hobo(float x, float y, float size, float depth) : Person(x, y, size*.33f, size*.65f, depth) {
  type |= HOBO;
  renderSize = Vector2f(size, size);
  textureBase = "hobo";
  stringstream num;
  num << rand()%2;
  deathAnim = num.str();
}

bool Hobo::isSatisfied() {
  return (money >= 5);
}

