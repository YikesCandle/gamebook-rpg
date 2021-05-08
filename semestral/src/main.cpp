#include <iostream>
#include <ncurses.h>
#include <string>
#include "menu.hpp"

using namespace std;


int main(int argc, char **argv)
{
  initscr();
  noecho();
  curs_set(0);

  int yMax, xMax;
  getmaxyx(stdscr, yMax, xMax);
  WINDOW *win = newwin(yMax / 2, xMax / 2, yMax / 4, xMax / 4);
  box(win, 0, 0);

  MenuBar menuBar;
  mvwprintw(win, 0, xMax / 4 - 11, " ***** DARKLAND ***** ");
  int choice;
  string STATE = "Lunch"; // 0 main menu, 1 character select
  bool first;
  while ( (choice = wgetch(win)) )
  {
    if (STATE == "Lunch")
    {
      // Init menubar
      if (first)
      {
        Menu menus[3] = {
        Menu("New Game"),
        Menu("Load Game"),
        Menu("Quit Game")
        };
        MenuBar menuBar(win, menus, 3, 2, 2);
        first = false;
        menuBar.draw();
      }
      if (menuBar.handleTrigger(choice))
      {
        STATE = MenuBar
        break;
      }
      menuBar.draw();
    }
  }
  endwin();
  return 0;

}
