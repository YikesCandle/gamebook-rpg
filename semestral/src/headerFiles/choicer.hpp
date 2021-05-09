#ifndef CHOICER_H
#define CHOICER_H

#include <ncurses.h>
#include <string>
#include <vector>
#include "game.hpp"

class Choice
{
 
    public:

        Choice(std::string text);

    private:

        friend class Choicer;

        void draw(WINDOW * screen, bool selected = false);

        std::string text; // to display
};

class Choicer
{
    public:

        Choicer(std::vector<Choice> choiceList);

        int ask_for_choice();

    private:

        void init_window();
        void close_window();
        int select_next(int selected);
        int seelct_previous(int selected);
        void draw(int selected);

        std::vector<Choice> choiceList;
        // screen coords
        int x1;
        int y1;
        int x2;
        int y2;
        WINDOW *window;
        int start;
};

#endif // CHOICER_H