#ifndef CHOICER_H
#define CHOICER_H

#include <ncurses.h>
#include <string>
#include <vector>
#include <algorithm>
#include "other.hpp"

//! Menu bar class, helps the Player interact with the game
class Choicer
{
    public:

        Choicer(std::vector<std::string> _choiceList);
        //!Choicer(std::vector<std::string>, ToShow showItems);

        template <class ToShow = std::shared_ptr<class Item> >
        int ask_for_choice(std::vector<ToShow> showObjecs = std::vector<ToShow>());

    private:

        //! initialize window, is called while creating the menu bar
        void init_window();
        //! clears the window
        void close_window();
        //! increase variable "selected" if isn't selected the last option
        void select_next();
        //! decrease variable "selected" if isn't selected the first option
        void selct_previous();
        //! shows the menubar
        void draw();

        std::vector<std::string> choiceList;
        //! screen coords
        int x1; int y1;
        int x2; int y2;
        int selected;
        bool showing = false;
        std::vector<int> edges;
        WINDOW *window;
};

//! interact with the player and returns selected option
//! optional argument is vector of objests to which showInfo method is called, helps with visualization
template <typename ToShow>
int Choicer::ask_for_choice(std::vector<ToShow> showObjecs)
{
    if (!showObjecs.empty())
        showObjecs[this->selected]->showInfo();
    draw();
    bool enter    = false;
    flushinp();
    while (int key = wgetch(window))
    {
        if (!showObjecs.empty())
            showObjecs[this->selected]->closeInfo();
        switch (key)
        {
            case KEY_RIGHT:  select_next();      break;
            case KEY_LEFT:   selct_previous();   break;
            case 10:  enter    = true;    break;
            default:;
        }
        if (enter)
            break;
        if (!showObjecs.empty())
            showObjecs[this->selected]->showInfo();
        draw();
    }
    werase(this->window);
    wrefresh(this->window);
    delwin(this->window);
    return selected;
}

#endif //! CHOICER_H