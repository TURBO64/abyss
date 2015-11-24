#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>
#include <ctime>
#include <cstdlib>

#include "map.hpp"
#include "monster.hpp"

const int WORLD_HEIGHT = 8;
const int WORLD_WIDTH = 8;

class World {
  public:
    Map worldArray[WORLD_HEIGHT][WORLD_WIDTH] = {
      {MAP_XX, MAP_XX, MAP_XX, MAP_XX, MAP_SE, MAP_SW, MAP_SE, MAP_OU},
      {MAP_XX, MAP_XX, MAP_SE, MAP_EW, MAP_NW, MAP_NS, MAP_NS, MAP_XX},
      {MAP_XX, MAP_XX, MAP_NS, MAP_XX, MAP_XX, MAP_NE, MAP_NW, MAP_XX},
      {MAP_XX, MAP_XX, MAP_NE, MAP_EW, MAP_EW, MAP_SW, MAP_XX, MAP_XX},
      {MAP_XX, MAP_XX, MAP_XX, MAP_XX, MAP_XX, MAP_NE, MAP_SW, MAP_XX},
      {MAP_XX, MAP_SE, MAP_EW, MAP_EW, MAP_SW, MAP_XX, MAP_NS, MAP_XX},
      {MAP_XX, MAP_NS, MAP_XX, MAP_XX, MAP_NS, MAP_XX, MAP_NS, MAP_XX},
      {MAP_IN, MAP_NW, MAP_XX, MAP_XX, MAP_NE, MAP_EW, MAP_NW, MAP_XX}
    };
    std::vector<Monster> mobIndex = {
      Monster("Rat", 'r', BROWN),
      Monster("Spider", 'x', DARKGREY),
      Monster("Snake", 's', GREEN)
    };
    World();
    ~World();
};

#endif
