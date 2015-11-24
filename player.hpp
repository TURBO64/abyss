#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include "screen.hpp"
#include "map.hpp"

class Player {
  private:
    std::string name;
    char glyph;
    int color;
  public:
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
