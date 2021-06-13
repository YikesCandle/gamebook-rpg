#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include <vector>
#include <string>
#include <ncurses.h>
#include <map>
#include <memory>
#include "other.hpp"

struct Enemy
{
        Enemy();
        Enemy randomEnemy(int level, int id);
        void showInfo();
        void closeInfo();

        std::string name;
        std::string startOfFight;
        std::string attack;
        Stats stats;
        int actualHealth;
        int attactType;
        int level;
        int experience;
        std::vector<std::shared_ptr<Item> > drops;
        std::vector<Ability> abilities;
        WINDOW *infoWindow;
};

#endif // ENEMY_H



