#ifndef MONSTER_HPP
#define MONSTER_HPP

#include <string>
#include <vector>
#include "screen.hpp"

class Monster {
  private:
    std::string name;
    char glyph;
    int color;
  public:
    int x, y;
    Monster(std::string name, char glyph, int color);
    ~Monster();
    void draw(Screen &scr);
    const char * getName();
};

#endif
