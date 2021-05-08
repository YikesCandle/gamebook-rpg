#include "menu.hpp"

using namespace std;

Menu::Menu(string text)
: text(text)
{ }

MenuBar::MenuBar(WINDOW * win, Menu * menus, int size, int y, int x)
: window(win),
  menuList(menus),
  numMenus(size),
  currentMenu(0),
  yPos(y),
  xPos(x)
{
    keypad(this->window, true);
    getmaxyx(stdscr, this->maxY, this->maxX);
}

void MenuBar::draw()
{
    string text;
    for (int i = 0; i < this->numMenus; ++i)
    {
        text = this->menuList[i].text;
        if (i == this->currentMenu)
        {
            wattron(this->window, A_STANDOUT);
        }
        mvwprintw(this->window, this->yPos + i * 2, this->xPos, text.c_str());
        wattroff(this->window, A_STANDOUT);
    }
}

bool MenuBar::handleTrigger(int trigger)
{
    // returns true when enter entered
    switch (trigger)
    {
    case KEY_UP:
        if (this->currentMenu != 0)
            this->currentMenu -= 1;
        break;
    case KEY_DOWN:
        if (this->currentMenu != this->numMenus - 1)
            this->currentMenu += 1;
        break;
    case KEY_ENTER: 
        return true; 
    default:;
    }
    return false;
}

std::string MenuBar::actual_menu()
{
    return this->menuList[this->currentMenu].text;
}


