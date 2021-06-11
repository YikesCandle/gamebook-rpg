#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <memory>
#include "other.hpp"

struct Enemy
{
        Enemy();
        std::string name;
        std::string startOfFight;
        std::string attack;
        Stats stats;
        int actualHealth;
        int attactType;
        int level;
        int experience;
        std::map<double, std::shared_ptr<Item> > drops;
        std::vector<Ability> abilities;
};

#endif // ENEMY_H



