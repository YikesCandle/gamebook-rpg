#ifndef ACTION_H
#define ACTION_H


#include <iostream>
#include <memory>
#include <unistd.h>
#include "enemy.hpp"
#include "player.hpp"
#include "other.hpp"


class Action
{
    public:
        Action() = default;
        virtual ~Action() = default;
        virtual void Evoke(Player & player);
        std::string get_type();
    protected:
        std::string type;
        int timeNeeded;
};

//-------------------------------------------

class Fight : public Action
{
    public:
        Fight(const Enemy & enemy);
        virtual ~Fight() = default;
        virtual void Evoke(Player & player) override;
    private:
        void pausePrint(std::vector<std::string> & lines, WINDOW * fightWindow, int p1, int p2, int e1, int e2);
        Enemy enemy;
        bool attacking;
};

class Travel : public Action
{
    public:
        virtual ~Travel() = default;
        virtual void Evoke(Player & player) override;
    private:
        int toX;
        int toY;

        
};

class Shop : public Action
{
    public:
        virtual ~Shop() = default;
        virtual void Evoke(Player & player) override;
    private:
};

#endif ACTION_H