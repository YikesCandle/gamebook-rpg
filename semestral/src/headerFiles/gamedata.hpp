#ifndef GAMEDATA_H
#define GAMEDATA_H

class Player
{
    public:
    
    private:
};

class Time
{
    public:
    
    private:
};

class Map
{
    public:

    private:
        struct Location
        {
            
        };
};
class GameData
{
    public:

         GameData() = default;
        ~GameData() = default;


    private:
        Player player;
        Time time;
        Map map;
};


#endif GAMEDATA_H