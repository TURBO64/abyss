#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <curses.h>

// pretty colors
const int GREY         =  0;
const int RED          =  1;
const int GREEN        =  2;
const int BROWN        =  3;
const int BLUE         =  4;
const int MAGENTA      =  5;
const int CYAN         =  6;
const int LIGHTWHITE   =  7;
const int LIGHTRED     =  8;
const int LIGHTGREEN   =  9;
const int YELLOW       = 10;
const int LIGHTBLUE    = 11;
const int LIGHTMAGENTA = 12;
const int LIGHTCYAN    = 13;
const int DARKGREY     = 14;

class Screen {
  private:
    void setColor(int c);
    void unsetColor();
  public:
    Screen();
    ~Screen();
    void cls();
    void addChar(int y, int x, char glyph, int color);
};

#endif
