#include <iostream>
#include <ncurses.h>
#include <string>
#include "headerFiles/game.hpp"

using namespace std;


int main(int argc, char **argv)
{
  Game game;
  game.Start();
  return 0;
}
