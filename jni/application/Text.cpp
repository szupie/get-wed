#include "Text.h"

Text::Text(float x, float y, float depth, string text, string font) {
  this->x = x;
  this->y = y;
  this->depth = depth;
  this->text = new string(text);
  this->justify = ZENI_CENTER;
  this->font = font;
}
  
Text::~Text() {}

void Text::render() {
  get_Fonts()[String(font)].render_text(String(*text), Point2f(x, y), Color(), justify);
}

void Text::render(Point2f pos) {
  get_Fonts()[String(font)].render_text(String(*text), pos, Color(), justify);
}
