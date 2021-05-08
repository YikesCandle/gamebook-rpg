#ifndef CHOICER_H
#define CHOICER_H

#include <ncurses.h>
#include <string>
#include <vector>

class Choice
{
 
    public:

        Choice(std::string text, int x, int y);

    private:

        friend class Choicer;

        void draw(WINDOW * screen, bool selected = false);

        std::string text; // to display
        int x;            // location
        int y;
};

class Choicer
{
    public:

        Choicer(std::vector<Choice> choiceList, int y1, int x1, int y2, int x2);

        int ask_for_choice();

    private:

        int select_next(int selected);
        int seelct_previous(int selected);
        void draw(int selected);

        WINDOW *window;
        std::vector<Choice> choiceList;
};

#endif // CHOICER_H