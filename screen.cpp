#include "screen.hpp"

Screen::Screen() {
  initscr();
  start_color();
  use_default_colors();
  noecho();
  keypad(stdscr, true);
  curs_set(0);
  init_pair( 0, COLOR_WHITE, COLOR_BLACK);
  init_pair( 1, COLOR_RED, COLOR_BLACK);
  init_pair( 2, COLOR_GREEN, COLOR_BLACK);
  init_pair( 3, COLOR_YELLOW, COLOR_BLACK);
  init_pair( 4, COLOR_BLUE, COLOR_BLACK);
  init_pair( 5, COLOR_MAGENTA, COLOR_BLACK);
  init_pair( 6, COLOR_CYAN, COLOR_BLACK);
  init_pair( 7, COLOR_WHITE, COLOR_BLACK);
  init_pair( 8, COLOR_RED, COLOR_BLACK);
  init_pair( 9, COLOR_GREEN, COLOR_BLACK);
  init_pair(10, COLOR_YELLOW, COLOR_BLACK);
  init_pair(11, COLOR_BLUE, COLOR_BLACK);
  init_pair(12, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(13, COLOR_CYAN, COLOR_BLACK);
  init_pair(14, COLOR_BLACK, COLOR_BLACK);
}

Screen::~Screen() {
  endwin();
}

// clear screen
void Screen::cls() {
  clear();
}

// set color
void Screen::setColor(int c) {
  if(c < 7) {
    attron(COLOR_PAIR(c));
  }
  else {
    attron(A_BOLD);
    attron(COLOR_PAIR(c));
  }
}

// unset color
void Screen::unsetColor() {
  attroff(A_BOLD);
  for(int c = 0; c < 15; c++) {
    attroff(COLOR_PAIR(c));
  }
}

// print a character at specified location
void Screen::addChar(int y, int x, char glyph, int color) {
  this->setColor(color);
  mvaddch(y, x, glyph);
  this->unsetColor();
}
