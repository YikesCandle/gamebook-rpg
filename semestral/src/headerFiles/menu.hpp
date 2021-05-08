#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>
#include <ncurses.h>

class Menu
{   
    public:
        Menu(std::string text);
    private:
        friend class MenuBar;
        std::string text;
};


class MenuBar
{
    public:
        MenuBar(WINDOW * win, Menu * menus, int size, int y, int x);
        void draw();
        bool handleTrigger(int ch);
        std::string actual_menu();
    private:
        WINDOW *window;
        Menu *menuList;
        int numMenus;
        int currentMenu;
        int maxX;
        int maxY;
        int yPos;
        int xPos;

};

#endif //MENU_H