#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <ncurses.h>
#include "other.hpp"


class Player
{
    public:
        Player();
        std::string get_name();
        void set_name(const std::string & playerName);
        void newGamePlayer();
        void add_experience(int exp);
        std::vector<Ability> get_abilities();
        void showInfo();
        void closeInfo();
    private:
        friend class Fight;
        friend class GameData;
        Stats stats;
        int actualHealth;
        int actualMana;
        int level;
        bool alive;
        int experience;
        Inventory inventory;
        std::vector<Ability> abilities;
        WINDOW * infoWindow;


        std::string name;
        int actualPositionX;
        int actualPositionY;

        
};
#endif // PLAYER_H