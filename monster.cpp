#include "monster.hpp"

Monster::Monster(std::string name, char glyph, int color) {
  this->name = name;
  this->glyph = glyph;
  this->color = color;
}

Monster::~Monster() {

}

void Monster::draw(Screen &scr) {
  // draw Monster glyph to screen
  scr.addChar(this->y, this->x, this->glyph, this->color);
}

const char * Monster::getName() {
  return this->name.c_str();
}
