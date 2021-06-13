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
        virtual void showInfo();
        virtual void closeInfo();
        bool isRepeatable();
    protected:
        std::string type;
        int timeNeeded;
        bool repeatable = false;
};

struct Location
{
    void showInfo();
    void closeInfo();

    std::string name;
    int y;
    int x;
    int level;
    bool visited;
    std::string type;
    std::vector<std::shared_ptr<Action> > avaliableActions;
    std::vector<std::shared_ptr<Action> > travelAction;
    WINDOW * locationWindow;
};

//-------------------------------------------

class Fight : public Action
{
    public:
        Fight(const Enemy & enemy);
        virtual ~Fight() = default;
        virtual void Evoke(Player & player) override;
        virtual void showInfo() override;
        virtual void closeInfo() override;
    private:
        void pausePrint(std::vector<std::string> & lines, WINDOW * fightWindow, int p1, int p2, int e1, int e2);
        Enemy enemy;
        bool attacking;
};

class Travel : public Action
{
    public:
        virtual ~Travel() = default;
        Travel() = default;
        Travel(Location & location);
        virtual void Evoke(Player & player) override;
        virtual void showInfo() override;
        virtual void closeInfo() override;
    private:
        Location location;

        
};

class Shop : public Action
{
    public:
        virtual ~Shop() = default;
        virtual void Evoke(Player & player) override;
    private:
};

#endif ACTION_H