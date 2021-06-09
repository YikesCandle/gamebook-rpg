#ifndef CHOICER_H
#define CHOICER_H

#include <ncurses.h>
#include <string>
#include <vector>
#include <algorithm>
#include "game.hpp"

class Choicer
{
    public:

        Choicer(std::vector<std::string> _choiceList);

        int ask_for_choice();

    private:

        void init_window();
        void close_window();
        void select_next();
        void selct_previous();
        void draw();

        std::vector<std::string> choiceList;
        // screen coords
        int x1; int y1;
        int x2; int y2;
        int selected;
        std::vector<int> edges;
        WINDOW *window;
};

#endif // CHOICER_H