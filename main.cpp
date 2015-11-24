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

int main() {

  // seed rand
  srand(time(NULL));

  // gamestates
  bool gameOver = false;
  bool gameWin = false;
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

  // load starting map
  Map currentmap = world.worldArray[player.worldY][player.worldX];

  // init screen
  Screen scr;

  // begin main loop //////////////////////////////////////////////////////////
  while(!gameOver) {
    // check if player has won
    if(player.worldY == 0 and player.worldX == 8) {
      gameOver = true;
      gameWin = true;
      break;
    }

    // load current map
    currentmap = world.worldArray[player.worldY][player.worldX];

    // monster iterator
    std::vector<Monster>::iterator mob;

    // move mobs
    for(mob = currentmap.mobs.begin(); mob < currentmap.mobs.end(); mob++) {
      mob->y = mob->y + 1;
      mob->x = mob->x + 1;
    }

    // refresh
    scr.cls();

    // draw map
    currentmap.draw(scr);

    // draw mobs
    for(mob = currentmap.mobs.begin(); mob < currentmap.mobs.end(); mob++) {
      mob->draw(scr);
    }

    // draw player
    player.draw(scr);

    // player name
    mvprintw(0, 41, "%s the Unworthy", player.getName());

    // debug info
    mvprintw(2, 41, "Turn: %d", gameTurn);
    mvprintw(3, 41, "Player coords: %d, %d", player.x, player.y);
    mvprintw(4, 41, "World coords: %d, %d", player.worldX, player.worldY);
    mvprintw(19, 0, "Use hjkl to move left, down, up, right.");
    mvprintw(20, 0, "Use yubn to move diagonally.");

    // mob coords
    int i = 0;
    for(mob = currentmap.mobs.begin(); mob < currentmap.mobs.end(); mob++) {
      mvprintw(6 + i, 41, "%s coords: %d, %d", mob->getName(), mob->x, mob->y);
      i++;
    }

    // get input
    input = getch();

    // key bindings
    switch(input) {
      // movement
      case 'h': // left
        if(player.mv(0, -1, currentmap) ) gameTurn++;
        else continue;
        break;
      case 'j': // down
        if(player.mv(1, 0, currentmap) ) gameTurn++;
        else continue;
        break;
      case 'k': // up
        if(player.mv(-1, 0, currentmap) ) gameTurn++;
        else continue;
        break;
      case 'l': // right
        if(player.mv(0, 1, currentmap) ) gameTurn++;
        else continue;
        break;
      case 'y': // up-left
        if(player.mv(-1, -1, currentmap) ) gameTurn++;
        else continue;
        break;
      case 'u': // up-right
        if(player.mv(-1, 1, currentmap) ) gameTurn++;
        else continue;
        break;
      case 'b': // down-left
        if(player.mv(1, -1, currentmap) ) gameTurn++;
        else continue;
        break;
      case 'n': // down-right
        if(player.mv(1, 1, currentmap) ) gameTurn++;
        else continue;
        break;

      // game commands
      case 'q':
        gameOver = true;
        break;

      // invalid command
      default:
        continue;
    }
  }
  // end main loop ////////////////////////////////////////////////////////////

  if(gameWin) {
    scr.cls();
    mvprintw(12, 36, "You win!");
    getch();
  }

  // end game
  return 0;
}
