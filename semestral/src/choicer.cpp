#include "choicer.hpp"

using namespace std;

Choicer::Choicer(vector<Choice>  choiceList_, int y1, int x1, int y2, int x2)
: choiceList(choiceList_), window(newwin(y1, x1, y2, x2))
{
    keypad(this->window, true); // allow keypad
}
int Choicer::select_next(int selected)
{
    selected++;
    if (selected >= (int)this->choiceList.size())
        selected = 0;
    return selected;
}
int Choicer::seelct_previous(int selected)
{
    selected--;
    if (selected < 0)
        selected = (int)this->choiceList.size();
    return selected;
}
void Choicer::draw(int selected)
{
    string text;
    for (size_t i = 0; i < choiceList.size(); ++i)
    {
        bool attrON = false;
        if ((int)i == selected)
            attrON = true;
        choiceList[i].draw(this->window, attrON);
    }
}
int Choicer::ask_for_choice()
{
    int  selected = 0;
    bool enter    = false;
    while (int key = getch())
    {
        switch (key)
        {
            case KEY_DOWN:  selected = select_next(selected);     break;
            case KEY_UP:    selected = seelct_previous(selected); break;
            case KEY_ENTER: enter    = true;                      break;
            default:
        }
        draw(selected);
        refresh();
        if (enter)
            break;
    }
    return selected;
}
//----------------------------------------------------------------------
void Choice::draw(WINDOW * window, bool selected = false)
{
    if (selected)
        wattron(window, A_STANDOUT);
    mvwprintw(window, this->x, this->y, this->text.c_str());
    wattroff(window, A_STANDOUT);
}
Choice::Choice(string text_, int x_, int y_)
: text(text_), x(x_), y(y_)
{ }
