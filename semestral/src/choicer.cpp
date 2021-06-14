#include "headerFiles/choicer.hpp"

using namespace std;

Choicer::Choicer(vector<string>  _choiceList)
: choiceList(_choiceList), x1(SCREEN_WIDTH), y1(3), x2(0), y2(SCREEN_HEIGHT), selected(0)
{
    this->window = newwin(y1, x1, y2, x2);
    keypad(this->window, true);

    int width = this->x1;
    int edge = 0;
    while (edge < (int)this->choiceList.size())
    {
        this->edges.push_back(edge);
        int sumOfMenuWidth = 0;
        for (int i = edge; i < (int)this->choiceList.size(); ++i)
        {
            if (sumOfMenuWidth + this->choiceList[i].length() + 2 > width - 2)
                break;
            sumOfMenuWidth += this->choiceList[i].length() + 2;
            edge = i;
        }
        edge++;
    }
}
void Choicer::Choicer::select_next()
{
    selected = ++selected == (int)this->choiceList.size() ? (int)this->choiceList.size() - 1 : selected;
}
void Choicer::selct_previous()
{
    selected = --selected == -1 ? 0 : selected;
}
void Choicer::draw()
{
    werase(window);
    box(this->window, 0, 0);
    wrefresh(window);
    int first = 0;
    int last = 0;
    for (int i = (int)edges.size() - 1; i >= 0; --i)
    {
        if (edges[i] <= selected)
        {
            first = edges[i];
            if (i ==  (int)edges.size() - 1)
                last = choiceList.size() - 1;
            else
                last = edges[i + 1] - 1;
            break;
        }
    }
    int actualXPosition = 1;
    for (int i = first; i <= last; ++i)
    {
        if (i == selected)
            wattron(window, A_STANDOUT);
        mvwprintw(window, 1, actualXPosition, choiceList[i].c_str());
        wattroff(window, A_STANDOUT);
        actualXPosition += choiceList[i].length() + 2;
    }
    wrefresh(window);
}
//----------------------------------------------------------------------
