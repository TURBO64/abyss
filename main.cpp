#include "screen.hpp"
#include "map.hpp"
#include "player.hpp"
#include "monster.hpp"
#include "world.hpp"

#include <ctime>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <string>

void moveMobs(Map *currentmap, Player &player);
void movePlayer(int dy, int dx, Player &player, Map *currentmap);

int main() {
  // seed rand
  srand(time(NULL));

  // gamestates
  bool gameOver = false;
  int gameTurn = 0;

  // input handler
  int input = 0;

  // ask for player name
  std::string name;
  std::cout << "Enter your name: ";
  getline(std::cin, name);
  if(name.empty()) name = "No-Name";

  // init player
  Player player(name, '@', GREEN);

  // player starting positions
  player.worldY = 7;
  player.worldX = 0;
  player.y = MAP_HEIGHT / 2;
  player.x = MAP_WIDTH / 2;

  // init world
  World world;

  // create currentmap pointer
  Map * currentmap = &world.worldArray[player.worldY][player.worldX];

  // init screen
  Screen scr;

  // begin main loop //////////////////////////////////////////////////////////
  while(!gameOver) {
    // load current map
    currentmap = &world.worldArray[player.worldY][player.worldX];

    // move mobs
    moveMobs(currentmap, player);

    // check if player is dead
    if(player.hp < 1) {
      gameOver = true;
      break;
    }

    // refresh
    scr.cls();

    // draw map
    currentmap->draw(scr);

    // draw mobs
    std::vector<Monster>::iterator mob;
    for(mob = currentmap->mobs.begin(); mob < currentmap->mobs.end(); mob++) {
      mob->draw(scr);
    }

    // draw player
    player.draw(scr);

    // player name and title
    if(player.lvl == 1) player.title = "Unworthy";
    if(player.lvl == 2) player.title = "Mediocre";
    if(player.lvl == 3) player.title = "Adept";
    if(player.lvl == 4) player.title = "Ruthless";
    if(player.lvl == 5) player.title = "Unstoppable";
    mvprintw(0, 41, "%s the %s", player.name.c_str(), player.title.c_str());
    mvprintw(1, 41, "Player HP: %d", player.hp);

    // debug info
    mvprintw(2, 41, "Turn: %d", gameTurn);
    mvprintw(3, 41, "Player coords: %d, %d", player.x, player.y);
    mvprintw(4, 41, "World coords: %d, %d", player.worldX, player.worldY);

    // mob coords
    int i = 0;
    for(mob = currentmap->mobs.begin(); mob < currentmap->mobs.end(); mob++) {
      mvprintw(6 + i, 41, "%s coords: %d, %d, HP: %d", mob->getName(), mob->x, mob->y, mob->hp);
      i++;
    }

    // get input
    input = getch();

    // key bindings
    switch(input) {
      // movement
      case KEY_B1: case KEY_LEFT: case 'h': // left
        movePlayer(0, -1, player, currentmap);
        break;
      case KEY_C2: case KEY_DOWN: case 'j': // down
        movePlayer(1, 0, player, currentmap);
        break;
      case KEY_A2: case KEY_UP: case 'k': // up
        movePlayer(-1, 0, player, currentmap);
        break;
      case KEY_B3: case KEY_RIGHT: case 'l': // right
        movePlayer(0, 1, player, currentmap);
        break;
      case KEY_A1: case 'y': // up-left
        movePlayer(-1, -1, player, currentmap);
        break;
      case KEY_A3: case 'u': // up-right
        movePlayer(-1, 1, player, currentmap);
        break;
      case KEY_C1: case 'b': // down-left
        movePlayer(1, -1, player, currentmap);
        break;
      case KEY_C3: case 'n': // down-right
        movePlayer(1, 1, player, currentmap);
        break;

      // game commands
      case 'q':
        gameOver = true;
        break;

      // invalid command
      default:
        continue;
    }

    // check if player has won
    if(player.worldY == 0 and player.worldX == 8) {
      gameOver = true;
      break;
    }

    // add turn
    gameTurn++;
  }
  // end main loop ////////////////////////////////////////////////////////////

  // end game
  return 0;
}

void moveMobs(Map *currentmap, Player &player) {
  std::vector<Monster>::iterator mob;
  for(mob = currentmap->mobs.begin(); mob < currentmap->mobs.end(); mob++) {
    int dy = 0, dx = 0;
    int newx = 0, newy = 0;
    int ydistance = 0, xdistance = 0;

    // calculate distance from player to mob
    if(player.y < mob->y) ydistance = mob->y - player.y;
    else ydistance = player.y - mob->y;
    if(player.x < mob->x) xdistance = mob->x - player.x;
    else xdistance = player.x - mob->x;

    // follow player
    if(ydistance <= 8 and xdistance <= 8) {
      if(mob->y > player.y) dy = -1;
      if(mob->y < player.y) dy = 1;
      if(mob->x > player.x) dx = -1;
      if(mob->x < player.x) dx = 1;
    }

    // new mob position
    newx = mob->x + dx;
    newy = mob->y + dy;

    // move mob
    if(currentmap->isFree(newy, newx)) {
      if(newx != player.x or newy != player.y) {
        mob->x = newx;
        mob->y = newy;
      }
      // attack player
      else {
        player.hp--;
      }
    }
  }
}

void movePlayer(int dy, int dx, Player &player, Map *currentmap) {
  // predict new position
  int newx = player.x + dx;
  int newy = player.y + dy;

  // collision detection/combat
  bool blocked = false;

  // check for terrain block
  if(!currentmap->isFree(newy, newx)) blocked = true;

  // check for mob collisions
  std::vector<Monster>::iterator mob;
  for(mob = currentmap->mobs.begin(); mob < currentmap->mobs.end(); mob++) {
    if(newx == mob->x and newy == mob->y) {
      blocked = true;

      // hit monster
      int hitChance = rand() % 2; // chance to hit/miss
      if(hitChance == 1) {
        mob->hp -= player.atk;

        // kill monster
        if(mob->hp < 1) {
          currentmap->mobs.erase(mob);

          // blood and guts
          currentmap->mapArray[newy][newx] = currentmap->tile_blood;
        }
        break;
      }
    }
  }
  if(!blocked) {
    player.y = newy;
    player.x = newx;
  }
  // move east in world
  if(newx == MAP_WIDTH) {
    player.worldX++;
    player.x = 0;
  }
  // move west in world
  if(newx == -1) {
    player.worldX--;
    player.x = MAP_WIDTH - 1;
  }
  // move north in world
  if(newy == -1) {
    player.worldY--;
    player.y = MAP_HEIGHT - 1;
  }
  // move south in world
  if(newy == MAP_HEIGHT) {
    player.worldY++;
    player.y = 0;
  }
}
