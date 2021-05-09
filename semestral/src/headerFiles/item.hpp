#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <vector>
#include "other.hpp"

class Item
{
    public:
        virtual void Use() = 0;
    private:
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

#endif // ITEM_H