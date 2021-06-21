#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <ncurses.h>
#include <algorithm>
#include <fstream>
#include "other.hpp"

//!! Player class manage every action associated with player and holds his basic data
class Player
{
    public:
        //!! constructor does nothing
        Player();
        std::string get_name();
        void set_name(const std::string & playerName);

        //!! sets Player basic data, should be called before starting new game
        void newGamePlayer();

        //!! adds experience to players experience (opperator +=)
        void add_experience(int exp);

        //!! returns players abilities
        std::vector<Ability> get_abilities();

        //!! shows player info (creates independent ncurses window)
        void showInfo();
        //!! shows window that was opened by Player::showInfo()
        void closeInfo();

        //!! return reference to the player inventory
        std::vector<std::shared_ptr<Item> > & get_inventory();
        //! return reference to the player gear
        std::vector<std::shared_ptr<Item> > & get_equip();

        //! adds item to equip
        void addToEquip(std::shared_ptr<Item> & item);
        //! removes item to equip, item is recognized by ITEM_ID
        void removeFromEquip(std::shared_ptr<Item> & item);
        //! shows and process item actions - Use/Euip, Drop
        void itemManipulate(std::shared_ptr<Item> & item);

        //! looks at player gear for item, returns true if the item was found
        bool isItemEquiped(std::shared_ptr<Item> & item);

        //! returns true if player is alive
        bool isAlive();
        //! sets Player current location
        void setCoords(int y, int x);

        //! read player data from a file
        int read(std::ifstream & file);
        //! write player data to a file
        int write(std::ofstream & file);

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
        //! independent window for Player::Info function
        WINDOW * infoWindow;

        std::string name;
        int actualPositionX;
        int actualPositionY;

};
#endif //! PLAYER_H