#ifndef GAMEDATA_H
#define GAMEDATA_H

#include "player.hpp"
#include <string>
#include <vector>
#include <memory>
#include <ncurses.h>
#include "action.hpp"
#include "other.hpp"
#include "enemy.hpp"

//class Time
//{
//    public:
//        // todo
//    
//    private:
//        int time; // minutes
//};

class Map
{
    public:
        Map();
        void showMap();
        void newGameMap();
    private:
        friend class Game;
        friend class GameData;
        std::vector<std::vector<Location> > map;
};
class GameData
{
    public:

         GameData() = default;
        ~GameData() = default;

        std::vector<Ability> get_playerAbilities();
        void set_playerAbilities(const std::vector<Ability> & ab);
        Location & getCurrentLocation();
        // data manipulation
    private:
        friend class Game;
        Player player;
        //Time time;
        Map map;
};


#endif // GAMEDATA_H