#include "headerFiles/enemy.hpp"

Enemy::Enemy()
{
    
}

void Enemy::showInfo()
{
    char number[40] = {};
    this->infoWindow = newwin(SCREEN_HEIGHT, SCREEN_WIDTH, 0, 0);
    werase(infoWindow);
    box(infoWindow, 0, 0);
    mvwprintw(infoWindow, 1, (SCREEN_WIDTH - 2) / 2 - 5, "-- Enemy --");
    mvwprintw(infoWindow, 2, 1, "Name: ");
    wprintw(infoWindow, this->name.c_str());
    sprintf(number, " lvl %d", this->level);
    wprintw(infoWindow, number);
    mvwprintw(infoWindow, 4, 1, "Stats: ");

    mvwprintw(infoWindow, 4, 8, "HP: ");
    sprintf(number, "\t%d", this->stats.health);
    wprintw(infoWindow, number);

    mvwprintw(infoWindow, 5, 8, "Deff: ");
    sprintf(number, "\t%d", this->stats.defence);
    wprintw(infoWindow, number);

    mvwprintw(infoWindow, 6, 8, "Str: ");
    sprintf(number, "\t%d", this->stats.strenght);
    wprintw(infoWindow, number);

    mvwprintw(infoWindow, 7, 8, "Int: ");
    sprintf(number, "\t%d", this->stats.inteligence);
    wprintw(infoWindow, number);
    
    mvwprintw(infoWindow, 9, 1, "Abilities: ");
    if (this->abilities.empty())
        wprintw(infoWindow, "none");
    else
        for (size_t i = 0; i < abilities.size(); ++i)
            mvwprintw(infoWindow, 9 + i, 12, abilities[i].name.c_str());

    wrefresh(infoWindow);
}
void Enemy::closeInfo()
{
    if (infoWindow == NULL)
        return;
    werase(infoWindow);
    wrefresh(infoWindow);
    delwin(infoWindow);
    infoWindow = NULL;
}

Enemy Enemy::randomEnemy(int level, int id)
{
    std::shared_ptr<Item> potion1 = Consumable().randomItem(level, 0, 0);
    std::shared_ptr<Item> potion2 = Consumable().randomItem(level, 1, 0);
    std::shared_ptr<Item> potion3 = Consumable().randomItem(level, 2, 0);
    switch(id)
    {
        case 0:
        {
            Enemy enemy;
            enemy.stats = Stats(10 * level, 3 * level, 1 * level, 0);
            enemy.name = "wolf";
            enemy.level = level;
            enemy.experience = 10 * level;
            enemy.actualHealth = enemy.stats.health;
            enemy.startOfFight = "You were attacked by wolf! You cannot run. You must fight!";
            Ability ab;
            ab.name = "claw attack";
            ab.intScale = 0;
            ab.strengthScale = 5;
            ab.timeNeeded = 4;
            enemy.abilities.push_back(ab);
            Ability ab2;
            ab2.name = "bite";
            ab2.intScale = 0;
            ab2.strengthScale = 3;
            ab2.timeNeeded = 2;
            enemy.abilities.push_back(ab2);
            std::shared_ptr<Item> drop1 = Equipable().randomItem(level, 6, rand() % 50 + 50);
            std::shared_ptr<Item> drop2 = Equipable().randomItem(level, 8, rand() % 50 + 50);
            if (rand() % 6 == 0)
                enemy.drops.push_back(drop2);
            if (rand() % 6 == 0)
                enemy.drops.push_back(drop1);
            if (rand() % 5 == 0)
                enemy.drops.push_back(potion1);
            if (rand() % 5 == 0)
                enemy.drops.push_back(potion2);
            if (rand() % 10 == 0)
                enemy.drops.push_back(potion3);
            return enemy;
        }
        case 1:
        {
            Enemy enemy;
            enemy.stats = Stats(30 * level, 2 * level, 3 * level, 1 * level);
            enemy.name = "Iron golem";
            enemy.level = level;
            enemy.experience = 30 * level;
            enemy.actualHealth = enemy.stats.health;
            enemy.startOfFight = "You were attacked by Iron goem! You cannot run. You must fight!";
            Ability ab;
            ab.name = "stomp";
            ab.intScale = 0;
            ab.strengthScale = 7;
            ab.timeNeeded = 10;
            enemy.abilities.push_back(ab);
            Ability ab2;
            ab2.name = "punch";
            ab2.intScale = 0;
            ab2.strengthScale = 2;
            ab2.timeNeeded = 5;
            enemy.abilities.push_back(ab2);
            std::shared_ptr<Item> drop1 = Equipable().randomItem(level, 5, rand() % 50 + 40);
            std::shared_ptr<Item> drop2 = Equipable().randomItem(level, 7, rand() % 50 + 40);
            std::shared_ptr<Item> drop3 = Equipable().randomItem(level, 2, rand() % 50 + 40);
            if (rand() % 5 == 0)
                enemy.drops.push_back(drop2);
            if (rand() % 10 == 0)
                enemy.drops.push_back(drop1);
            if (rand() % 13 == 0)
                enemy.drops.push_back(drop3);
            if (rand() % 5 == 0)
                enemy.drops.push_back(potion1);
            if (rand() % 5 == 0)
                enemy.drops.push_back(potion2);
            if (rand() % 10 == 0)
                enemy.drops.push_back(potion3);
            return enemy;
        }
        case 2:
        {
            Enemy enemy;
            enemy.stats = Stats(5 * level, 1 * level, 0, 3 * level);
            enemy.name = "magic frog";
            enemy.level = level;
            enemy.experience = 8 * level;
            enemy.actualHealth = enemy.stats.health;
            enemy.startOfFight = "You were attacked by magic frog! You cannot run. You must fight!";
            Ability ab;
            ab.name = "tongue shot";
            ab.intScale = 0;
            ab.strengthScale = 1;
            ab.timeNeeded = 1;
            enemy.abilities.push_back(ab);
            Ability ab2;
            ab2.name = "water magic";
            ab2.intScale = 4;
            ab2.strengthScale = 0;
            ab2.timeNeeded = 4;
            enemy.abilities.push_back(ab2);
            std::shared_ptr<Item> drop1 = Equipable().randomItem(level, 3, rand() % 50 + 20);
            std::shared_ptr<Item> drop2 = Equipable().randomItem(level, 4, rand() % 50 + 40);
            if (rand() % 15 == 0)
                enemy.drops.push_back(drop1);
            if (rand() % 10 == 0)
                enemy.drops.push_back(drop2);
            if (rand() % 5 == 0)
                enemy.drops.push_back(potion1);
            if (rand() % 5 == 0)
                enemy.drops.push_back(potion2);
            if (rand() % 10 == 0)
                enemy.drops.push_back(potion3);
            return enemy;
        }
        case 3:
        {
            Enemy enemy;
            enemy.stats = Stats(12 * level, 3 * level, 1 * level, 1 * level);
            enemy.name = "peasant";
            enemy.level = level;
            enemy.experience = 12 * level;
            enemy.actualHealth = enemy.stats.health;
            enemy.startOfFight = "You were attacked by poor peasant! You cannot run. You must fight!";
            Ability ab;
            ab.name = "punch";
            ab.intScale = 0;
            ab.strengthScale = 3;
            ab.timeNeeded = 3;
            enemy.abilities.push_back(ab);
            Ability ab2;
            ab2.name = "pitchfork attack";
            ab2.intScale = 0;
            ab2.strengthScale = 3;
            ab2.timeNeeded = 6;
            enemy.abilities.push_back(ab2);
            std::shared_ptr<Item> drop1 = Equipable().randomItem(level, 0, rand() % 50 + 40);
            std::shared_ptr<Item> drop2 = Equipable().randomItem(level, 1, rand() % 50 + 40);
            std::shared_ptr<Item> drop3 = Equipable().randomItem(level, 9, rand() % 50 + 40);
            if (rand() % 10 == 0)
                enemy.drops.push_back(drop1);
            if (rand() % 10 == 0)
                enemy.drops.push_back(drop2);
            if (rand() % 10 == 0)
                enemy.drops.push_back(drop3);
            if (rand() % 5 == 0)
                enemy.drops.push_back(potion1);
            if (rand() % 5 == 0)
                enemy.drops.push_back(potion2);
            if (rand() % 10 == 0)
                enemy.drops.push_back(potion3);
            return enemy;
        }
        case 4:
        {
            Enemy enemy;
            enemy.stats = Stats(25 * level, 4 * level, 2 * level, 1 * level);
            enemy.name = "bear";
            enemy.level = level;
            enemy.experience = 22 * level;
            enemy.actualHealth = enemy.stats.health;
            enemy.startOfFight = "You were attacked by huge bear! You cannot run. You must fight!";
            Ability ab;
            ab.name = "claw attack";
            ab.intScale = 0;
            ab.strengthScale = 6;
            ab.timeNeeded = 7;
            enemy.abilities.push_back(ab);
            Ability ab2;
            ab2.name = "roar wave";
            ab2.intScale = 2;
            ab2.strengthScale = 3;
            ab2.timeNeeded = 4;
            enemy.abilities.push_back(ab2);
            std::shared_ptr<Item> drop1 = Equipable().randomItem(level, 4, rand() % 50 + 50);
            std::shared_ptr<Item> drop2 = Equipable().randomItem(level, 5, rand() % 50 + 50);
            std::shared_ptr<Item> drop3 = Equipable().randomItem(level, 6, rand() % 50 + 50);
            if (rand() % 12 == 0)
                enemy.drops.push_back(drop1);
            if (rand() % 12 == 0)
                enemy.drops.push_back(drop2);
            if (rand() % 12 == 0)
                enemy.drops.push_back(drop3);
            if (rand() % 5 == 0)
                enemy.drops.push_back(potion1);
            if (rand() % 5 == 0)
                enemy.drops.push_back(potion2);
            if (rand() % 10 == 0)
                enemy.drops.push_back(potion3);
            return enemy;
        }
    }
    return Enemy();
}