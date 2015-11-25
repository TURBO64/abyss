#include "world.hpp"

World::World() {
  // loop through world array
  for(int y = 0; y < WORLD_HEIGHT; y++) {
    for(int x = 0; x < WORLD_WIDTH; x++) {
      // add mobs to maps (except first map)
      if(this->worldArray[y][x].mapType != MAP_IN) {
        // max number of mobs on map
        int maxMobs = rand() % 6;
        for(int n = 0; n < maxMobs; n++) {
          // select random mob
          int r = rand() % this->mobIndex.size();
          Monster mob = this->mobIndex[r];
          // randomize mob positions
          mob.y = 5 + rand() % (MAP_HEIGHT - 10);
          mob.x = 5 + rand() % (MAP_WIDTH - 10);
          // add mob to map's mob vector
          this->worldArray[y][x].mobs.push_back(mob);
        }
      }
    }
  }
}

World::~World() {

}
