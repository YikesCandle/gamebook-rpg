#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <ncurses.h>
#include <algorithm>
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
        std::vector<std::shared_ptr<Item> > & get_inventory();
        std::vector<std::shared_ptr<Item> > & get_equip();
        void addToEquip(std::shared_ptr<Item> & item);
        void removeFromEquip(std::shared_ptr<Item> & item);
        void itemManipulate(std::shared_ptr<Item> & item);
        bool isItemEquiped(std::shared_ptr<Item> & item);
        bool isAlive();

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
        std::vector<std::shared_ptr<Item> > equipedItems;
        std::vector<Ability> abilities;
        WINDOW * infoWindow;


        std::string name;
        int actualPositionX;
        int actualPositionY;

        
};
#endif // PLAYER_H