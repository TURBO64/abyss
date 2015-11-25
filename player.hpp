#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "screen.hpp"
#include "map.hpp"

#include <string>

class Player {
  private:
    char glyph;
    int color;
  public:
    std::string name;
    std::string title;
    int hp = 50;
    int lvl = 1;
    int x, y;
    int atk = lvl * 3;
    int worldX, worldY;
    Player(std::string name, char glyph, int color);
    ~Player();
    void draw(Screen &scr);
};

#endif
