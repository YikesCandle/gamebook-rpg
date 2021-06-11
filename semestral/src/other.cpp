#include "headerFiles/other.hpp"


using namespace std;

void show_text(std::vector<std::string> & text)
{
    WINDOW *storyWindow = newwin(SCREEN_HEIGHT - 2, SCREEN_WIDTH - 2, 1, 1);
    int numberOfPages = text.size();
    for (int page = 0; page < numberOfPages;)
    {
        wclear(storyWindow);
        mvwprintw(storyWindow, 0, 0, text[page].c_str());

        char pageInfo[6] = {};
        sprintf(pageInfo, "%d/%d", page + 1, numberOfPages);
        mvwprintw(storyWindow, SCREEN_HEIGHT - 3, 0, pageInfo);
        wrefresh(storyWindow);
        vector<string> choices;
        if (page == 0)
            choices = {"Continue"};
        else if (page != numberOfPages - 1)
            choices = {"Back", "Continue"};
        else
            choices = {"Back", "Finish"};
            
        Choicer menubar(choices);
        switch (menubar.ask_for_choice())
        {
            case 0: page += page == 0 ? 1 : -1; break;
            case 1: page += 1; break;
        }
    }
    wclear(storyWindow);
    wrefresh(storyWindow);
    delete(storyWindow);
}

int Ability::calculateDmg(int level, const Stats & attacker, const Stats & deffender)
{
    return (attacker.strenght - deffender.defence) * this->strengthScale + attacker.inteligence * intScale;
}