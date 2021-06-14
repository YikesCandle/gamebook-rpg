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

struct Stats
{
    Stats() = default;
    Stats(int h, int s, int d, int i);
    Stats & operator += (const Stats & s2);
    Stats & operator -= (const Stats & s2);
    int read(std::ifstream & file);
    int write(std::ofstream & file);

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

    Ability read(std::ifstream & file);
    void write(std::ofstream & file);
};

class Item
{
    public:
        virtual ~Item() = default;
        virtual std::shared_ptr<Item> randomItem(int level, int id, int state);
        std::string get_name();
        virtual std::string get_type();
        int get_level();
        int get_cost();
        virtual void showInfo();
        virtual void closeInfo();
        int getID() const;
        virtual int getFileType();
        virtual std::shared_ptr<Item> read(std::ifstream & file);
        virtual void write(std::ofstream & file);
    protected:
        std::string name;
        int level;
        int cost;
        int ID;
        int fileType;
        WINDOW * itemWindow;
};
class Equipable : public Item
{
    public:
        virtual ~Equipable() = default;
        virtual std::shared_ptr<Item> randomItem(int level, int id, int state) override;
        virtual void showInfo() override;
        virtual void closeInfo() override;
        Stats & get_stats();
        std::vector<Ability> & get_abilities();
        virtual std::string get_type() override;
        virtual int getFileType() override;

        virtual std::shared_ptr<Item> read(std::ifstream & file) override;
        virtual void write(std::ofstream & file) override;
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
        virtual void showInfo() override;
        virtual void closeInfo() override;
        int get_health();
        virtual int getFileType() override;

        virtual std::shared_ptr<Item> read(std::ifstream & file) override;
        virtual void write(std::ofstream & file) override;
    private:
        int health;
};

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

void show_text(std::vector<std::string> & text);



#endif // OTHER_H