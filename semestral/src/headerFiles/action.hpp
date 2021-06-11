#ifndef ACTION_H
#define ACTION_H


#include <iostream>
#include <memory>
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