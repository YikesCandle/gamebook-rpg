#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include <memory>
#include "other.hpp"

class Item
{
    public:
        virtual void Use() = 0;
    private:
        Stats stats;
        int level;
        int cost;
};
class Armor : public Item
{
    public:
        virtual void Use() = 0;
    private:
};
class Weapon : public Item
{
    public:
        virtual void Use() = 0;
    private:
};
class Consumable : public Item
{
    public:
        virtual void Use() = 0;
    private:
};

class Inventory
{
    public:
        void draw();
        void resize();
    private:
        int size;
        std::vector<std::shared_ptr<Item> > items;
};

class Player
{
    public:
    private:
        Stats stats;
        Inventory inventory;
        
};
#endif // PLAYER_H