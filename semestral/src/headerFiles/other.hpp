#ifndef OTHER_H
#define OTHER_H

#include <string>
#include <ncurses.h>
#include <vector>
#include <iostream>
#include "choicer.hpp"

static const int SCREEN_WIDTH = 66;
static const int SCREEN_HEIGHT = 18;

struct Stats
{
    int health = 0;
    int strenght = 0;
    int defence = 0;
    int inteligence = 0;
    int luck = 0;
};

struct Ability
{
    std::string name;
    int calculateDmg(int level, const Stats & attacker, const Stats & deffender);
    int strengthScale;
    int intScale;
    int timeNeeded;
};

class Item
{
    public:
    private:
        int level;
        int cost;
};
class Equipable : public Item
{
    public:

    private:
        Stats stats;
        std::string type;
        std::vector<Ability> abilities;
};

class Consumable : public Item
{
    public:
    private:
        Stats stats;
};

class Inventory
{
    public:
    private:
        friend class Player;
        int size;
        std::vector<std::shared_ptr<Item> > items;
};

void show_text(std::vector<std::string> & text);



#endif // OTHER_H