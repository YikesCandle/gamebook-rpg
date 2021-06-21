#include "headerFiles/enemy.hpp"


using namespace std;

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
    ifstream file("examples/enemies.txt");
    if (!file.is_open())
        throw runtime_error("Error while loading enemy from examples/enemies.txt");
    Enemy enemy;
    for (int i = 0; i < 3; ++i)
    {
        std::shared_ptr<Item> potion1 = Consumable().randomItem(level, i, 0);
        if (rand() % 5 == 0)
        enemy.drops.push_back(potion1);
    }
    string line;
    bool found = false;
    while (getline(file, line))
    {
        char tmp[20];
        sprintf(tmp, "ENEMY_ID: %d", id);
        if (line == string(tmp))
        {
            found = true;
            break;
        }
    }
    if (!found)
    {
        char errortxt[100];
        sprintf(errortxt, "Enemy ID not found: %d", id);
        throw runtime_error(errortxt);
    }

    string str;
    int h, s, d, i;
    // Stats
    if (!(file >> str >> h >> s >> d >> i) || str != "STATS:")
        throw runtime_error("Error while loading enemy from examples/enemies.txt | error at stats");
    enemy.stats = Stats(h * level, s * level, d * level, i * level);
    // name
    string trashstr;
    if (!(file >> trashstr >> str) || trashstr != "NAME:")
        throw runtime_error("Error while loading enemy from examples/enemies.txt | error at name");
    enemy.name = str;
    enemy.level = level;
    enemy.experience = enemy.stats.health;
    enemy.actualHealth = enemy.stats.health;
    int number;
    if (!(file >> str >> number) || number <= 0 || number > 10 || str != "ABILITIES:")
        throw runtime_error("Error while loading enemy from examples/enemies.txt | error at number of abilities");
    for (int i = 0; i < number; ++i)
    {
        Ability ab;
        // ability name
        string teststr;
        if (!(file >> teststr >> str) || teststr != "ABILITY_NAME:")
            throw runtime_error("Error while loading enemy from examples/enemies.txt | ability name");
        ab.name = str;
        if (!(file >> str >> h >> s >> d) || str != "ABILITY_DATA:")
            throw runtime_error("Error while loading enemy from examples/enemies.txt | ability data");
        ab.intScale = h;
        ab.strengthScale = s;
        ab.timeNeeded = d;
        enemy.abilities.push_back(ab);
    }
    if (!(file >> str >> number) || number < 0 || number > 10 || str != "DROPS:")
        throw runtime_error("Error while loading enemy from examples/enemies.txt | error number of drops");
    for (int i = 0; i < number; ++i)
    {
        int item;
        if (!(file >> str >> item >> h|| item < 0 || item > 9 || h <= 0 || str != "ITEM:"))
            throw runtime_error("Error while loading enemy from examples/enemies.txt | error - item");
        try
        {
            std::shared_ptr<Item> drop1 = Equipable().randomItem(level, item, rand() % 50 + 40);
            if (rand() % h == 0)
                enemy.drops.push_back(drop1);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            throw;
        }
    }
    file.close();
    return enemy;
}
