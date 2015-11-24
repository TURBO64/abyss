#ifndef MAP_HPP
#define MAP_HPP

#include "screen.hpp"
#include "monster.hpp"

#include <vector>
#include <ctime>
#include <cstdlib>


// global map constants
const int MAP_WIDTH = 40;
const int MAP_HEIGHT = 18;

const int MAP_EW = 0;  // east and west
const int MAP_NS = 1;  // north and south
const int MAP_NW = 2;  // north and west
const int MAP_NE = 3;  // north and east
const int MAP_SW = 4;  // south and west
const int MAP_SE = 5;  // south and east
const int MAP_IN = 6;  // start map
const int MAP_OU = 7;  // end map
const int MAP_XX = 99; // blank map

struct Tile {
  char glyph;
  int color;
  bool passable;
};

class Map {
  private:
    void rect(int startY, int startX, int height, int width, Tile tile);
    void brush(int y, int x, Tile tile);
  public:
    int mapType;
    Tile mapArray[MAP_HEIGHT][MAP_WIDTH];
    std::vector<Monster> mobs;
    Map(int mapType);
    ~Map();
    void draw(Screen &scr);
};

#endif
