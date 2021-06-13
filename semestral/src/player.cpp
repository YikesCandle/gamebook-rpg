#include "headerFiles/player.hpp"

using namespace std;

string Player::get_name()
{
    return this->name;
}
void Player::set_name(const string & playerName)
{
    this->name = playerName;
}

void Player::newGamePlayer()
{
    this->inventory.size = 5;
    this->stats.health = 100;
    this->actualHealth = 100;
    this->actualPositionX = 0;
    this->actualPositionY = 0;
    this->level = 1;
    this->stats.strenght = 1;
    Ability punch;
    punch.name = "punch";
    punch.strengthScale = 4;
    punch.timeNeeded = 3;
    punch.intScale = 0;
    this->abilities.push_back(punch);
    Ability kick;
    kick.name = "kick";
    kick.strengthScale = 1;
    kick.timeNeeded = 1;
    kick.intScale = 0;
    this->abilities.push_back(kick);
    this->alive = true;
}

void Player::add_experience(int exp)
{
    this->experience += exp;
}

std::vector<Ability> Player::get_abilities()
{
    return this->abilities;
}

Player::Player()
{
}

void Player::showInfo()
{
    char number[50] = {};
    this->infoWindow = newwin(SCREEN_HEIGHT, SCREEN_WIDTH, 0, 0);
    werase(infoWindow);
    box(infoWindow, 0, 0);
    mvwprintw(infoWindow, 1, (SCREEN_WIDTH - 2) / 2 - 6, "-- Player --");
    mvwprintw(infoWindow, 2, 1, "Name: ");
    wprintw(infoWindow, this->name.c_str());
    sprintf(number, " lvl %d", this->level);
    wprintw(infoWindow, number);
    mvwprintw(infoWindow, 4, 1, "Health: ");
    sprintf(number, "%d/%d", this->actualHealth, this->stats.health);
    wprintw(infoWindow, number);
    mvwprintw(infoWindow, 6, 1, "Stats: ");

    mvwprintw(infoWindow, 6, 8, "HP: ");
    sprintf(number, "\t%d", this->stats.health);
    wprintw(infoWindow, number);

    mvwprintw(infoWindow, 7, 8, "Deff: ");
    sprintf(number, "\t%d", this->stats.defence);
    wprintw(infoWindow, number);

    mvwprintw(infoWindow, 8, 8, "Str: ");
    sprintf(number, "\t%d", this->stats.strenght);
    wprintw(infoWindow, number);

    mvwprintw(infoWindow, 9, 8, "Int: ");
    sprintf(number, "\t%d", this->stats.inteligence);
    wprintw(infoWindow, number);
    
    mvwprintw(infoWindow, 11, 1, "Abilities: ");
    if (this->abilities.empty())
        wprintw(infoWindow, "none");
    else
        for (size_t i = 0; i < abilities.size(); ++i)
            mvwprintw(infoWindow, 11 + i, 12, abilities[i].name.c_str());

    wrefresh(infoWindow);
}
void Player::closeInfo()
{
    if (infoWindow == NULL)
        return;
    werase(infoWindow);
    wrefresh(infoWindow);
    delete(infoWindow);
    infoWindow = NULL;
}