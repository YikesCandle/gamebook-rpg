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

// unfinished class

//class Time
//{
//    public:
//        // todo
//    
//    private:
//        int time; // minutes
//};


// Game map, contains actual statue of the game, locations
class Map
{
    public:
        Map();
        // does nothing
        void showMap();
        // generates new Map - should be called before starting new game
        void newGameMap();
    private:
        friend class Game;
        friend class GameData;
        // map is just 2D map of Locations, Locations contain actions
        std::vector<std::vector<Location> > map;
};

// contains game Map and Player data
class GameData
{
    public:

         GameData() = default;
        ~GameData() = default;

        std::vector<Ability> get_playerAbilities();
        void set_playerAbilities(const std::vector<Ability> & ab);
        // return reference to a player Location
        Location & getCurrentLocation();
        // data manipulation
    private:
        friend class Game;
        Player player;
        //Time time;
        Map map;
};


#endif // GAMEDATA_H