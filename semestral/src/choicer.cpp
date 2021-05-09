#include "choicer.hpp"

using namespace std;

Choicer::Choicer(vector<Choice>  choiceList_)
: choiceList(choiceList_), x1(SCREEN_WIDTH), y1(5), x2(0), y2(SCREEN_HEIGHT), start(0)
{
    this->window = newwin(y1, x1, y2, x2);
    keypad(this->window, true);
}
int Choicer::Choicer::select_next(int selected)
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
            case KEY_RIGHT:  selected = select_next(selected);     break;
            case KEY_LEFT:   selected = seelct_previous(selected); break;
            case KEY_ENTER:  enter    = true;                      break;
            default:
        }
        draw(selected);
        wrefresh(this->window);
        if (enter)
            break;
    }
    werase(this->window);
    delete(this->window);
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
Choice::Choice(string text_)
: text(text_)
{ }
