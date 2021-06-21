#include "headerFiles/gamedata.hpp"


using namespace std;

Map::Map()
: map(16, vector<Location>(16, Location()))
{

}
void Map::showMap()
{

}

int Map::newGameMap()
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
        if (distance < 3)
        {
            location.level = 1;
        }
        else if (distance < 16)
        {
            location.level = rand() % (distance) + distance - 2;
        }
        else
        {
            location.level = rand() % (distance * 2) + distance;
        }
        if (i == 0 && j == 0)
        {
            try
            {
                for (int i = 0; i < 5; ++i)
                    this->map[0][0].avaliableActions.push_back(make_shared<Fight>(Fight(Enemy().randomEnemy(1, i))));
            }
            catch (const exception & e)
            {
                std::cerr << e.what() << '\n';
                return 1;
            }
        }
        else
        {
            int fights = rand() % 6 + 2;
            try
            {
                for (int f = 0; f < fights; ++f)
                    this->map[i][j].avaliableActions.push_back(make_shared<Fight>(Fight(Enemy().randomEnemy(location.level, rand() % 5))));
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
                return 1;
            }
        }
    }
    for (int i = 0; i < 16; ++i)
    for (int j = 0; j < 16; ++j)
    {
        if (i != 0)
            this->map[i][j].avaliableActions.push_back(make_shared<Travel>(Travel(this->map[i - 1][j])));
        if (i != 15)
            this->map[i][j].avaliableActions.push_back(make_shared<Travel>(Travel(this->map[i + 1][j])));
        if (j != 0)
            this->map[i][j].avaliableActions.push_back(make_shared<Travel>(Travel(this->map[i][j - 1])));
        if (j != 15)
            this->map[i][j].avaliableActions.push_back(make_shared<Travel>(Travel(this->map[i][j + 1])));
    }
    return 0;
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