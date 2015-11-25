#include "player.hpp"

Player::Player(std::string name, char glyph, int color) {
  this->name = name;
  this->glyph = glyph;
  this->color = color;
  this->worldY = 7;
  this->worldX = 0;
}

Player::~Player() {

}

void Player::draw(Screen &scr) {
  // draw player glyph to screen
  scr.addChar(this->y, this->x, this->glyph, this->color);
}
