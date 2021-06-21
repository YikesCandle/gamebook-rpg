#ifndef ACTION_H
#define ACTION_H


#include <iostream>
#include <memory>
#include <unistd.h>
#include <cmath>
#include <cstring>
#include "enemy.hpp"
#include "player.hpp"
#include "other.hpp"

//! every action can be inserted into location and be evoked
class Action
{
    public:
        Action() = default;
        virtual ~Action() = default;
        //! starts the action process
        virtual void Evoke(Player & player);
        std::string get_type();
        //! show info about current action, creates independent ncurses window
        virtual void showInfo();
        //! closes ncurses window opened by showInfo
        virtual void closeInfo();
        //! returns true, if IS repeatable, if action is repeatable then doesn't vanish after evoking
        bool isRepeatable();
    protected:
        std::string type;
        int timeNeeded;
        bool repeatable = false;
};

//! contains avaliable Actions
struct Location
{
    //! show info about current location, creates independent ncurses window
    void showInfo();
    //! closes ncurses window opened by showInfo
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

//!-------------------------------------------
//! Fight action, simulates fighting between player and enemy
class Fight : public Action
{
    public:
        Fight(const Enemy & enemy);
        virtual ~Fight() = default;
        //! starts the fighting simulation
        virtual void Evoke(Player & player) override;
        //! show info about current *Enemy*, creates independent ncurses window
        virtual void showInfo() override;
        //! closes ncurses window opened by showInfo
        virtual void closeInfo() override;
    private:
        //! prints the current state of the fight
        void pausePrint(std::vector<std::string> & lines, WINDOW * fightWindow, int p1, int p2, int e1, int e2);
        void enemyAttack(std::vector<std::string> & lines, WINDOW * fightWindow, Player & player, int & playerAbilityTime,
                            int & enemyAbilityTime, Ability & playerAbility, Ability & enemyAbility);
        int playerAttack(std::vector<std::string> & lines, WINDOW * fightWindow, Player & player, int & playerAbilityTime,
                            int & enemyAbilityTime, Ability & playerAbility, Ability & enemyAbility);
        void PEattack(std::vector<std::string> & lines, WINDOW * fightWindow, Player & player, int & playerAbilityTime,
                            int & enemyAbilityTime, Ability & playerAbility, Ability & enemyAbility);
        void enemyIsDead(Player & player);
        Enemy enemy;
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

#endif //!ACTION_H