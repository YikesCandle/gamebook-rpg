#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "other.hpp"


class Player
{
    public:
        Player();
        std::string get_name();
        void set_name(const std::string & playerName);
        void newGamePlayer();
        std::vector<Ability> get_abilities();
    private:
        friend class Fight;
        friend class GameData;
        Stats stats;
        int actualHealth;
        int actualMana;
        int level;
        Inventory inventory;
        std::vector<Ability> abilities;

        std::string name;
        int actualPositionX;
        int actualPositionY;

        
};
#endif // PLAYER_H