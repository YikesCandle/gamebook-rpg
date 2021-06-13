#include "headerFiles/other.hpp"


using namespace std;

void show_text(std::vector<std::string> & text)
{
    WINDOW *storyWindow = newwin(SCREEN_HEIGHT - 2, SCREEN_WIDTH - 2, 1, 1);
    int numberOfPages = text.size();
    for (int page = 0; page < numberOfPages;)
    {
        wclear(storyWindow);
        mvwprintw(storyWindow, 0, 0, text[page].c_str());

        char pageInfo[6] = {};
        sprintf(pageInfo, "%d/%d", page + 1, numberOfPages);
        mvwprintw(storyWindow, SCREEN_HEIGHT - 3, 0, pageInfo);
        wrefresh(storyWindow);
        vector<string> choices;
        if (page == 0)
            choices = {"Continue"};
        else if (page != numberOfPages - 1)
            choices = {"Back", "Continue"};
        else
            choices = {"Back", "Finish"};
            
        Choicer menubar(choices);
        switch (menubar.ask_for_choice())
        {
            case 0: page += page == 0 ? 1 : -1; break;
            case 1: page += 1; break;
        }
    }
    wclear(storyWindow);
    wrefresh(storyWindow);
    delete(storyWindow);
}

int Ability::calculateDmg(int level, const Stats & attacker, const Stats & deffender)
{
    int dmg = (attacker.strenght - deffender.defence) * this->strengthScale + attacker.inteligence * intScale;
    return dmg <= 0 ? 1 : dmg; 
}


void Item::showInfo()
{

}

void Item::closeInfo()
{

}

int Item::getID() const
{
    return ID;
}

Stats & Equipable::get_stats()
{
    return this->stats;
}

vector<Ability> & Equipable::get_abilities()
{
    return this->abilities;
}

Stats & Stats::operator += (const Stats & s2)
{
    this->health += s2.health;
    this->inteligence += s2.inteligence;
    this->defence += s2.defence;
    this->strenght += s2.strenght;
    return *this;
}

Stats & Stats::operator -= (const Stats & s2)
{
    this->health -= s2.health;
    this->inteligence -= s2.inteligence;
    this->defence -= s2.defence;
    this->strenght -= s2.strenght;
    return *this;
}

void Equipable::showInfo()
{
    char number[20] = {};
    this->itemWindow = newwin(SCREEN_HEIGHT, SCREEN_WIDTH, 0, 0);
    werase(itemWindow);
    box(itemWindow, 0, 0);
    mvwprintw(itemWindow, 1, (SCREEN_WIDTH - 2) / 2 - 5, "-- Item --");
    mvwprintw(itemWindow, 2, 1, "Name: ");
    wprintw(itemWindow, this->name.c_str());
    sprintf(number, " lvl %d", this->level);
    mvwprintw(itemWindow, 4, 1, "Type: ");
    wprintw(itemWindow, this->type.c_str());
    mvwprintw(itemWindow, 6, 1, "Quality: ");
    sprintf(number, "%d/100", this->quality);
    wprintw(itemWindow, number);

    mvwprintw(itemWindow, 8, 1, "Stats: ");

    mvwprintw(itemWindow, 8, 8, "HP:");
    sprintf(number, "\t+%d", this->stats.health);
    wprintw(itemWindow, number);

    mvwprintw(itemWindow, 9, 8, "Deff:");
    sprintf(number, "\t+%d", this->stats.defence);
    wprintw(itemWindow, number);

    mvwprintw(itemWindow, 10, 8, "Str:");
    sprintf(number, "\t+%d", this->stats.strenght);
    wprintw(itemWindow, number);

    mvwprintw(itemWindow, 11, 8, "Int:");
    sprintf(number, "\t+%d", this->stats.inteligence);
    wprintw(itemWindow, number);

    
    mvwprintw(itemWindow, 13, 1, "Abilities: ");
    if (this->abilities.empty())
        wprintw(itemWindow, "none");
    else
        for (size_t i = 0; i < abilities.size(); ++i)
            mvwprintw(itemWindow, 13 + i, 12, abilities[i].name.c_str());
    wrefresh(itemWindow);
}
void Equipable::closeInfo()
{
    if (itemWindow == NULL)
        return;
    werase(this->itemWindow);
    wrefresh(this->itemWindow);
    delete(itemWindow);
    itemWindow = NULL;
}

std::string Item::get_name()
{
    return this->name;
}
int Item::get_level()
{
    return this->level;
}
int Item::get_cost()
{
    return this->cost;
}

void Inventory::add_item(std::shared_ptr<Item> item)
{
    this->items.push_back(item);
}
void Inventory::delete_item(std::shared_ptr<Item> item)
{
    this->items.erase(find(items.begin(), items.end(), item));
}

Stats::Stats(int h, int s, int d, int i)
{
    this->defence = d;
    this->strenght = s;
    this->inteligence = i;
    this->health = h;
}

std::string Item::get_type()
{
    return string();
}
std::string Equipable::get_type()
{
    return this->type;
}

shared_ptr<Item> Item::randomItem(int level, int id, int state)
{
    throw (exception());
}
shared_ptr<Item> Equipable::randomItem(int level, int id, int state)
{
    switch(id)
    {
        case 0:
        {
            shared_ptr<Equipable> item = make_shared<Equipable>();
            item->type = "weapon";
            item->name = "basic dagger";
            item->level = level;
            item->cost = item->level * 10;
            item->quality = state;
            Stats stats;
            stats.strenght = 1 * level;

            Ability ability1;
            ability1.intScale = 0;
            ability1.name = "quick cut";
            ability1.strengthScale = 2;
            if (state > 90) ability1.strengthScale++;
            if (state < 60) ability1.strengthScale--;
            ability1.timeNeeded = 2;
            item->abilities.push_back(ability1);

            Ability ability2;
            ability2.intScale = 0;
            ability2.name = "heavy cut";
            ability2.strengthScale = 4;
            if (state > 90) ability2.strengthScale += 2;
            if (state < 60) ability2.strengthScale -= 2;
            ability2.timeNeeded = 5;
            item->abilities.push_back(ability2);
            if (state > 90)
            {
                stats.inteligence += 2 * level;
                stats.strenght += 1 * level;
                stats.defence += 0 * level;
                stats.health += 5 * level;
            }
            else if (state < 70)
            {
                stats.inteligence -= 0 * level;
                stats.strenght -= 1 * level;
                stats.defence -= 0 * level;
                stats.health -= 0 * level;
            }
            item->stats = stats;
            item->ID = ITEM_ID++;
            return item;
        }
        case 1:
        {
            shared_ptr<Equipable> item = make_shared<Equipable>();
            item->type = "weapon";
            item->name = "basic sword";
            item->level = level;
            item->cost = item->level * 15;
            item->quality = state;
            Stats stats;
            stats.strenght = 2 * level;

            Ability ability1;
            ability1.intScale = 0;
            ability1.name = "fast lunge";
            ability1.strengthScale = 3;
            if (state > 90) ability1.strengthScale++;
            if (state < 60) ability1.strengthScale--;
            ability1.timeNeeded = 3;
            item->abilities.push_back(ability1);

            Ability ability2;
            ability2.intScale = 0;
            ability2.name = "heavy sword attack";
            ability2.strengthScale = 7;
            if (state > 90) ability2.strengthScale += 3;
            if (state < 60) ability2.strengthScale -= 3;
            ability2.timeNeeded = 7;
            item->abilities.push_back(ability2);
            if (state > 90)
            {
                stats.inteligence += 0 * level;
                stats.strenght += 2 * level;
                stats.defence += 0 * level;
                stats.health += 8 * level;
            }
            else if (state < 70)
            {
                stats.inteligence -= 0 * level;
                stats.strenght -= 1 * level;
                stats.defence -= 0 * level;
                stats.health -= 0 * level;
            }
            item->stats = stats;
            item->ID = ITEM_ID++;
            return item;
        }
        case 2:
        {
            shared_ptr<Equipable> item = make_shared<Equipable>();
            item->type = "weapon";
            item->name = "hammer";
            item->level = level;
            item->cost = item->level * 15;
            item->quality = state;
            Stats stats;
            stats.strenght = 5 * level;

            Ability ability1;
            ability1.intScale = 0;
            ability1.name = "smash";
            ability1.strengthScale = 6;
            if (state > 90) ability1.strengthScale += 4;
            if (state < 60) ability1.strengthScale -= 2;
            ability1.timeNeeded = 10;
            item->abilities.push_back(ability1);
            if (state > 90)
            {
                stats.inteligence += 0 * level;
                stats.strenght += 2 * level;
                stats.defence += 0 * level;
                stats.health += 15 * level;
            }
            else if (state < 70)
            {
                stats.inteligence -= 0 * level;
                stats.strenght -= 2 * level;
                stats.defence -= 0 * level;
                stats.health -= 0 * level;
            }
            item->stats = stats;
            item->ID = ITEM_ID++;
            return item;
        }
        case 3:
        {
            shared_ptr<Equipable> item = make_shared<Equipable>();
            item->type = "weapon";
            item->name = "magic stick";
            item->level = level;
            item->cost = item->level * 30;
            item->quality = state;
            Stats stats;
            stats.strenght = 1 * level;
            stats.inteligence = 2 * level;

            Ability ability1;
            ability1.intScale = 5;
            ability1.name = "fireball";
            ability1.strengthScale = 0;
            if (state > 90) ability1.intScale += 2;
            if (state < 60) ability1.intScale -= 2;
            ability1.timeNeeded = 4;
            item->abilities.push_back(ability1);

            Ability ability2;
            ability2.intScale = 20;
            ability2.name = "supernova";
            ability2.strengthScale = 0;
            if (state > 90) ability2.intScale += 5;
            if (state < 60) ability2.strengthScale -= 5;
            ability2.timeNeeded = 15;
            item->abilities.push_back(ability2);
            if (state > 90)
            {
                stats.inteligence += 2 * level;
                stats.strenght += 0 * level;
                stats.defence += 0 * level;
                stats.health += 5 * level;
            }
            else if (state < 70)
            {
                stats.inteligence -= 1 * level;
                stats.strenght -= 1 * level;
                stats.defence -= 0 * level;
                stats.health -= 0 * level;
            }
            item->stats = stats;
            item->ID = ITEM_ID++;
            return item;
        }
        case 4:
        {
            shared_ptr<Equipable> item = make_shared<Equipable>();
            item->type = "armor";
            item->name = "leather armor";
            item->level = level;
            item->cost = item->level * 10;
            item->quality = state;
            Stats stats;
            stats.strenght = 1 * level;
            stats.inteligence = 2 * level;
            stats.defence = 1 * level;
            stats.health = 20 * level;
            if (state > 90)
            {
                stats.inteligence += 2 * level;
                stats.strenght += 0 * level;
                stats.defence += 1 * level;
                stats.health += 10 * level;
            }
            else if (state < 70)
            {
                stats.inteligence -= 1 * level;
                stats.strenght -= 1 * level;
                stats.defence -= 1 * level;
                stats.health -= 8 * level;
            }
            item->stats = stats;
            item->ID = ITEM_ID++;
            return item;
        }
        case 5:
        {
            shared_ptr<Equipable> item = make_shared<Equipable>();
            item->type = "armor";
            item->name = "plate armor";
            item->level = level;
            item->cost = item->level * 20;
            item->quality = state;
            Stats stats;
            stats.strenght = 2 * level;
            stats.defence = 2 * level;
            stats.health = 40 * level;
            if (state > 90)
            {
                stats.inteligence += 0 * level;
                stats.strenght += 2 * level;
                stats.defence += 2 * level;
                stats.health += 20 * level;
            }
            else if (state < 70)
            {
                stats.inteligence -= 0 * level;
                stats.strenght -= 1 * level;
                stats.defence -= 1 * level;
                stats.health -= 10 * level;
            }
            item->stats = stats;
            item->ID = ITEM_ID++;
            return item;
        }
        case 6:
        {
            shared_ptr<Equipable> item = make_shared<Equipable>();
            item->type = "helmet";
            item->name = "leather helmet";
            item->level = level;
            item->cost = item->level * 10;
            item->quality = state;
            Stats stats;
            stats.strenght = 0 * level;
            stats.inteligence = 3 * level;
            stats.defence = 1 * level;
            stats.health = 5 * level;
            if (state > 90)
            {
                stats.inteligence += 1 * level;
                stats.strenght += 0 * level;
                stats.defence += 1 * level;
                stats.health += 5 * level;
            }
            else if (state < 70)
            {
                stats.inteligence -= 1 * level;
                stats.strenght -= 0 * level;
                stats.defence -= 1 * level;
                stats.health -= 2 * level;
            }
            item->stats = stats;
            item->ID = ITEM_ID++;
            return item;
        }
        case 7:
        {
            shared_ptr<Equipable> item = make_shared<Equipable>();
            item->type = "helmet";
            item->name = "plate helmet";
            item->level = level;
            item->cost = item->level * 20;
            item->quality = state;
            Stats stats;
            stats.strenght = 3 * level;
            stats.inteligence = 0 * level;
            stats.defence = 1 * level;
            stats.health = 10 * level;
            if (state > 90)
            {
                stats.inteligence += 0 * level;
                stats.strenght += 2 * level;
                stats.defence += 1 * level;
                stats.health += 5 * level;
            }
            else if (state < 70)
            {
                stats.inteligence -= 0 * level;
                stats.strenght -= 1 * level;
                stats.defence -= 1 * level;
                stats.health -= 3 * level;
            }
            item->stats = stats;
            item->ID = ITEM_ID++;
            return item;
        }
        case 8:
        {
            shared_ptr<Equipable> item = make_shared<Equipable>();
            item->type = "boots";
            item->name = "leather boots";
            item->level = level;
            item->cost = item->level * 7;
            item->quality = state;
            Stats stats;
            stats.strenght = 1 * level;
            stats.inteligence = 2 * level;
            stats.defence = 1 * level;
            stats.health = 5 * level;
            if (state > 90)
            {
                stats.inteligence += 1 * level;
                stats.strenght += 0 * level;
                stats.defence += 1 * level;
                stats.health += 4 * level;
            }
            else if (state < 70)
            {
                stats.inteligence -= 1 * level;
                stats.strenght -= 1 * level;
                stats.defence -= 1 * level;
                stats.health -= 2 * level;
            }
            item->stats = stats;
            item->ID = ITEM_ID++;
            return item;
        }
        case 9:
        {
            shared_ptr<Equipable> item = make_shared<Equipable>();
            item->type = "boots";
            item->name = "plate boots";
            item->level = level;
            item->cost = item->level * 14;
            item->quality = state;
            Stats stats;
            stats.strenght = 2 * level;
            stats.inteligence = 0 * level;
            stats.defence = 2 * level;
            stats.health = 9 * level;
            if (state > 90)
            {
                stats.inteligence += 0;
                stats.strenght += 2 * level;
                stats.defence += 1 * level;
                stats.health += 4 * level;
            }
            else if (state < 70)
            {
                stats.inteligence -= 0;
                stats.strenght -= 2 * level;
                stats.defence -= 1 * level;
                stats.health -= 3 * level;
            }
            item->stats = stats;
            item->ID = ITEM_ID++;
            return item;
        }
    }
}