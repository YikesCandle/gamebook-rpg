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
        location.y = i;
        location.x = j;
        location.name = "location";
        switch (rand() % 4)
        {
            case 0: location.type = "forest"; break;
            case 1: location.type = "hill"; break;
            case 2: location.type = "field"; break;
            case 3: location.type = "town"; break;
        }
        int distance = i + j;
        if (distance < 5)
        {
            location.level = 1;
        }
        else if (distance < 120)
        {
            location.level = rand() % 20 - 10 + distance / 4;
            if (location.level < 2)
                location.level = 3;
        }
        else if (distance < 200)
        {
            location.level = rand() % 20 - 10 + distance / 3;
        }
        else if (distance < 250)
        {
            location.level = 100;
        }
    }
    for (int i = 0; i < 5; ++i)
        this->map[0][0].avaliableActions.push_back(make_shared<Fight>(Fight(Enemy().randomEnemy(1, i))));
    this->map[0][0].avaliableActions.push_back(make_shared<Travel>(Travel(this->map[1][0])));
    this->map[0][0].avaliableActions.push_back(make_shared<Travel>(Travel(this->map[0][1])));
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