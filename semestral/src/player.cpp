#include "headerFiles/player.hpp"

using namespace std;

string Player::get_name()
{
    return this->name;
}
void Player::set_name(const string & playerName)
{
    this->name = playerName;
}

void Player::newGamePlayer()
{
    this->inventory.size = 5;
    this->stats.health = 100;
    this->actualHealth = 100;
    this->actualPositionX = 0;
    this->actualPositionY = 0;
    this->level = 1;
    this->stats.strenght = 1;
    Ability punch;
    punch.name = "punch";
    punch.strengthScale = 4;
    punch.timeNeeded = 3;
    punch.intScale = 0;
    this->abilities.push_back(punch);
    Ability kick;
    punch.name = "kick";
    punch.strengthScale = 1;
    punch.timeNeeded = 1;
    punch.intScale = 0;
    this->abilities.push_back(kick);
}

std::vector<Ability> Player::get_abilities()
{
    return this->abilities;
}

Player::Player()
{
}