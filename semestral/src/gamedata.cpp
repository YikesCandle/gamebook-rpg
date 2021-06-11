#include "headerFiles/gamedata.hpp"


using namespace std;

Map::Map()
: map(16, vector<Location>(16, Location()))
{

}
void Map::showMap()
{

}

void Map::newGameMap()
{
    srand(time(nullptr));
    for (int i = 0; i < 16; ++i)
    for (int j = 0; j < 16; ++j)
    {
        Location & location = map[i][j];
        int distance = i + j;
        if (distance < 5)
        {
            location.type = 0;
            location.level = 1;
        }
        else if (distance < 120)
        {
            location.level = rand() % 20 - 10 + distance / 4;
            if (location.level < 2)
                location.level = 3;
            location.type = 1;
        }
        else if (distance < 200)
        {
            location.level = rand() % 20 - 10 + distance / 3;
            location.type = 2;
        }
        else if (distance < 250)
        {
            location.level = 100;
            location.type = 3;
        }
    }
    Enemy opp;
    opp.stats.health = 20;
    opp.actualHealth = 20;
    opp.stats.strenght = 4;
    opp.level = 2;
    opp.startOfFight = "You were attacked by wolf! You cannot run. You must fight!";
    opp.name = "wolf";
    Ability ab;
    ab.name = "whatever";
    ab.intScale = 0;
    ab.strengthScale = 3;
    ab.timeNeeded = 2;
    opp.abilities.push_back(ab);
    this->map[0][0].avaliableActions.push_back(make_shared<Fight>(Fight(opp)));
}

std::vector<Ability> GameData::get_playerAbilities()
{
    return this->player.abilities;
}
void GameData::set_playerAbilities(const std::vector<Ability> & ab)
{
    this->player.abilities = ab;
}

Location & GameData::getCurrentLocation()
{
    return this->map.map[this->player.actualPositionY][this->player.actualPositionX];
}