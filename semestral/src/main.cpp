#include <iostream>
#include <ncurses.h>
#include <string>
#include "headerFiles/game.hpp"

using namespace std;


int main(int argc, char **argv)
{
  Game game;
  try
  {
    game.Start();
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    vector<string> txt = {"something totally unexpected happened -> ending the game"};
    show_text(txt);
    game.End();
    return 1;
  }
  
  return 0;
}
