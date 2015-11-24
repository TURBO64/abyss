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
    int x, y;
    int dx, dy = 0;
    int worldX, worldY;
    Player(std::string name, char glyph, int color);
    ~Player();
    void draw(Screen &scr);
    bool mv(int dy, int dx, Map &currentmap);
    const char * getName();
};

#endif
