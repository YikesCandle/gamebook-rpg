#ifndef ACTION_H
#define ACTION_H


#include <iostream;
#include <memory>
#include "enemy.hpp"
#include "gamedata.hpp"

class Action
{
    public:
        virtual void Evoke() = 0;
    private:
        int timeNeeded;
};

//-------------------------------------------

class Fight : public Action
{
    public:
        virtual void Evoke() override;
    private:
        Enemy enemy;
};

class Travel : public Action
{
    public:
        virtual void Evoke() override;
    private:
        int fromX;
        int fromY;
        int toX;
        int toY;

        
};

class Shop : public Action
{
    public:
        virtual void Evoke() override;
    private:
};

#endif ACTION_H