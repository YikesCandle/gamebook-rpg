#ifndef GAMEDATA_H
#define GAMEDATA_H

#include "player.hpp"
#include <string>
#include <vector>
#include "action.hpp"

class Time
{
    public:
        // todo
    
    private:
        int time; // minutes
};

class Map
{
    public:
        void showMap();

    private:
        struct Location
        {
            std::string name;
            int level;
            bool visited;
            int type;
            std::vector<Action> avaliableActions;
            std::vector<Action> travelAction;
        };
        std::vector<Location> map;
};
class GameData
{
    public:

         GameData() = default;
        ~GameData() = default;
        // data manipulation

    private:
        Player player;
        Time time;
        Map map;
};


#endif GAMEDATA_H