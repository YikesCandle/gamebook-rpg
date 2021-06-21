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
        //! generates random enemy
        Enemy randomEnemy(int level, int id);
        //! shows info about Enemy on independent ncurses window
        void showInfo();
        //! closes window opened by showInfo method
        void closeInfo();

        std::string name;
        //! text on the beginning of the fight
        std::string startOfFight;
        std::string attack;
        Stats stats;
        int actualHealth;
        int attactType;
        int level;
        int experience;
        //! items that enemy will drop after it is defeated in the fight with a player
        std::vector<std::shared_ptr<Item> > drops;
        //! abilities that enemy can use
        std::vector<Ability> abilities;
        WINDOW *infoWindow;
};

#endif //! ENEMY_H



