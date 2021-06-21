#ifndef OTHER_H
#define OTHER_H

#include <string>
#include <ncurses.h>
#include <vector>
#include <iostream>
#include <memory>
#include <algorithm>
#include <limits.h>
#include <climits>
#include <fstream>
#include "choicer.hpp"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern int ITEM_ID;

//! primitive struct that holds stats (5 x int value), contains usefull methods
struct Stats
{
    Stats() = default;
    Stats(int h, int s, int d, int i);

    Stats & operator += (const Stats & s2);
    Stats & operator -= (const Stats & s2);

    //! read stats from a file
    int read(std::ifstream & file);
    //! write stats to a file
    int write(std::ofstream & file);

    int health = 0;
    int strenght = 0;
    int defence = 0;
    int inteligence = 0;
    int luck = 0;
};

//! defines player/enemy abilities/skills
struct Ability
{
    std::string name;
    //! returns exact amout of damage that entity will cause after using this ability
    int calculateDmg(int level, const Stats & attacker, const Stats & deffender);
    int strengthScale;
    int intScale;
    int timeNeeded;

    //! reads Ability from a file
    Ability read(std::ifstream & file);
    //! write Ability to a file
    int write(std::ofstream & file);
};

//! every instance of this class can be inserted into players inventar or gear 
class Item
{
    public:
        virtual ~Item() = default;
        //! generates random item and returns it
        virtual std::shared_ptr<Item> randomItem(int level, int id, int state);
        std::string get_name();
        virtual std::string get_type();
        int get_level();
        int get_cost();

        //! shows info on independent ncurses screen
        virtual void showInfo();
        //! closes window opened by Item::showInfo
        virtual void closeInfo();
        int getID() const;
        //! does nothing
        virtual int getFileType();

        //! virtual method that reads Item from a file
        virtual std::shared_ptr<Item> read(std::ifstream & file);
        //! virtual method that writes Item data to a file
        virtual int write(std::ofstream & file);
    protected:
        std::string name;
        int level;
        int cost;
        int ID;
        int fileType;
        WINDOW * itemWindow;
};

//! inherited from Item class, Euipables can be inserted to player inventar and gear
class Equipable : public Item
{
    public:
        virtual ~Equipable() = default;
        //! generates random Euipable item
        virtual std::shared_ptr<Item> randomItem(int level, int id, int state) override;

        //! shows info on independent window
        virtual void showInfo() override;
        //! close window that was opened by showInfo method, must be called after, not before
        virtual void closeInfo() override;
        //! returns reference to Item stats
        Stats & get_stats();
        std::vector<Ability> & get_abilities();
        virtual std::string get_type() override;
        //! does nothing
        virtual int getFileType() override;

        //! reads Equipable item from a file, returns it
        virtual std::shared_ptr<Item> read(std::ifstream & file) override;
        //! writes Equipable item from a file
        virtual int write(std::ofstream & file) override;
    private:
        Stats stats;
        std::string type;
        std::vector<Ability> abilities;
        int quality;
};

class Consumable : public Item
{
    public:
        virtual ~Consumable() = default;
        virtual std::shared_ptr<Item> randomItem(int level, int id, int state) override;
        //! shows info on independent window
        virtual void showInfo() override;
        //! close window that was opened by showInfo method, must be called after, not before
        virtual void closeInfo() override;
        int get_health();
        //! does nothing
        virtual int getFileType() override;

        //! reads Consumable item from a file, returns it
        virtual std::shared_ptr<Item> read(std::ifstream & file) override;
        //! writes Consumable item from a file
        virtual int write(std::ofstream & file) override;
    private:
        int health;
};

//! help class for Player, contains vector of items, does nothing more
class Inventory
{
    public:
        void add_item(std::shared_ptr<Item> item);
        void delete_item(std::shared_ptr<Item> item);
        int read(std::ifstream & file);
        int write(std::ofstream & file);
    private:
        friend class Player;
        int size;
        std::vector<std::shared_ptr<Item> > items;
};

//! shows text on independent ncurses window
void show_text(std::vector<std::string> & text);

#endif //! OTHER_H