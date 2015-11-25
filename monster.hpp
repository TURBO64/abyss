#ifndef MONSTER_HPP
#define MONSTER_HPP

#include "screen.hpp"

#include <string>
#include <vector>

class Monster {
  private:
    std::string name;
    char glyph;
    int color;
  public:
    int x, y;
    int hp = 5;
    Monster(std::string name, char glyph, int color);
    ~Monster();
    void draw(Screen &scr);
    const char * getName();
};

#endif
