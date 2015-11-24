#include "map.hpp"
#include <ctime>
#include <cstdlib>

Map::Map(int mapType) {

  // set mapType
  this->mapType = mapType;

  // tile definitions (glyph, color, passable)
  Tile tile_floor = {'.', CYAN, true};
  Tile tile_wall  = {'#', DARKGREY, false};
  Tile tile_water = {'~', BLUE, true};
  Tile tile_stalagmite = {'^', CYAN, false};
  Tile tile_light = {'.', LIGHTCYAN, true};

  // generate cave
  this->rect(0, 0, MAP_HEIGHT, MAP_WIDTH, tile_wall); // walls first

  // cut out floor with brush
  for(int n = 0; n < 99; n++) {
    int tx = 4 + rand() % (MAP_WIDTH - 8);
    int ty = 4 + rand() % (MAP_HEIGHT - 7);
    this->brush(ty, tx, tile_floor);
  }

  // add exits
  if(this->mapType == MAP_EW) {
    this->rect((MAP_HEIGHT / 2) - 2, 0, 4, MAP_WIDTH, tile_floor);
  }
  if(this->mapType == MAP_NS) {
    this->rect(0, MAP_WIDTH / 2 - 3, MAP_HEIGHT, 6, tile_floor);
  }
  if(this->mapType == MAP_NW) {
    this->rect((MAP_HEIGHT / 2) - 2, 0, 4, MAP_WIDTH / 2, tile_floor);
    this->rect(0, MAP_WIDTH / 2 - 3, MAP_HEIGHT / 2, 6, tile_floor);
  }
  if(this->mapType == MAP_NE) {
    this->rect((MAP_HEIGHT / 2) - 2, MAP_WIDTH / 2, 4, MAP_WIDTH / 2, tile_floor);
    this->rect(0, MAP_WIDTH / 2 - 3, MAP_HEIGHT / 2, 6, tile_floor);
  }
  if(this->mapType == MAP_SW) {
    this->rect((MAP_HEIGHT / 2) - 2, 0, 4, MAP_WIDTH / 2, tile_floor);
    this->rect(MAP_HEIGHT / 2, MAP_WIDTH / 2 - 3, MAP_HEIGHT / 2, 6, tile_floor);
  }
  if(this->mapType == MAP_SE) {
    this->rect((MAP_HEIGHT / 2) - 2, MAP_WIDTH / 2, 4, MAP_WIDTH / 2, tile_floor);
    this->rect(MAP_HEIGHT / 2, MAP_WIDTH / 2 - 3, MAP_HEIGHT / 2, 6, tile_floor);
  }
  if(this->mapType == MAP_IN) {
    this->rect((MAP_HEIGHT / 2) - 2, MAP_WIDTH / 2, 4, MAP_WIDTH / 2, tile_floor);
  }
  if(this->mapType == MAP_OU) {
    this->rect((MAP_HEIGHT / 2) - 2, 0, 4, MAP_WIDTH, tile_floor);
    this->rect((MAP_HEIGHT / 2) - 2, MAP_WIDTH - 3, 4, 3, tile_light);
    this->rect((MAP_HEIGHT / 2) - 1, MAP_WIDTH - 4, 2, 4, tile_light);
  }
  if(this->mapType == MAP_XX) {
    this->rect(0, 0, MAP_HEIGHT, MAP_WIDTH, tile_water);
  }

  // add stalagmites
  int numStalagmites = rand() % 6;
  for(int n = 0; n < numStalagmites; n++) {
    int tx = 5 + rand() % (MAP_WIDTH - 10);
    int ty = 5 + rand() % (MAP_HEIGHT - 10);
    if(this->mapArray[ty][tx].passable) {
      this->mapArray[ty][tx] = tile_stalagmite;
    }
  }

  // add water
  int isWater = rand() % 8;
  if(isWater == 1) {
    int tx = 7 + rand() % (MAP_WIDTH - 12);
    int ty = 7 + rand() % (MAP_HEIGHT - 11);
    for(int n = 0; n < 3; n++) {
      int xmod = (rand() % 4) - 2;
      int ymod = (rand() % 4) - 2;
      this->brush(ty + ymod, tx + xmod, tile_water);
    }
  }
}

Map::~Map() {

}

void Map::draw(Screen &scr) {
  for(int y = 0; y < MAP_HEIGHT; y++) {
    for(int x = 0; x < MAP_WIDTH; x++) {
      scr.addChar(y, x, this->mapArray[y][x].glyph, this->mapArray[y][x].color);
    }
  }
}

void Map::rect(int startY, int startX, int height, int width, Tile tile) {
  int endY = startY + height;
  int endX = startX + width;
  for(int y = startY; y < endY; y++) {
    for(int x = startX; x < endX; x++) {
      this->mapArray[y][x] = tile;
    }
  }
}

void Map::brush(int y, int x, Tile tile) {
  y = y - 1;
  x = x - 2;
  this->rect(y - 1, x + 1, 1, 3, tile);
  this->rect(y, x, 2, 5, tile);
  this->rect(y + 2, x + 1, 1, 3, tile);
}
