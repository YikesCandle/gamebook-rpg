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

void Player::addToEquip(shared_ptr<Item> & item)
{
    this->equipedItems.push_back(item);
    Equipable * tmp = dynamic_cast<Equipable *>(&(*item));

    this->stats += tmp->get_stats();
    for (Ability & ab : tmp->get_abilities())
        this->abilities.push_back(ab);
}

void Player::removeFromEquip(std::shared_ptr<Item> & item)
{
    this->equipedItems.erase(find_if(equipedItems.begin(), equipedItems.end(), [item](shared_ptr<Item> & A) -> bool
    {
        return A->getID() == item->getID();
    }));
    Equipable * tmp = dynamic_cast<Equipable *>(&(*item));

    this->stats -= tmp->get_stats();
    for (Ability & ab : tmp->get_abilities())
    {
        this->abilities.erase(
            find_if(abilities.begin(), abilities.end(), [ab](Ability & A) -> bool
                {
                    return A.name == ab.name;
                })
        );
    }
}

 bool Player::isItemEquiped(std::shared_ptr<Item> & item)
 {
     return find_if(equipedItems.begin(), equipedItems.end(), [item](shared_ptr<Item> & A) -> bool
    {
        return A->getID() == item->getID();
    })!= equipedItems.end();
 }

void Player::itemManipulate(shared_ptr<Item> & item)
{
    Equipable * tmp = dynamic_cast<Equipable *>(&(*item));
    if (tmp != nullptr)
    {
        item->showInfo();
        while (true)
        {
            vector<string> choices = {"Back"};
            vector<shared_ptr<Item> > showObjects = {item, item, item};
            if (isItemEquiped(item))
                choices.push_back("Unequip");
            else
                choices.push_back("Equip");
            choices.push_back("Drop");
            Choicer choicer(choices);
            switch (choicer.ask_for_choice(showObjects))
            {
                case 0: this->closeInfo(); return;
                case 1:
                {
                    if (isItemEquiped(item))
                        this->removeFromEquip(item);
                    else
                    {
                        auto it = find_if(equipedItems.begin(), equipedItems.end(), [item](shared_ptr<Item> & A) -> bool
                        {
                            return A->get_type() == item->get_type();
                        });
                        if (it == equipedItems.end())
                            this->addToEquip(item);
                        else
                        {
                            vector<string> txt = {"You already have this type of item equiped.", 
                                        "You can have only one piece of every equipable item type at the same time"};
                            show_text(txt);
                        }
                    }
                    break;
                }
                case 2:
                {
                    if (isItemEquiped(item))
                    {
                        vector<string> txt = {"You cannot drop equiped item."};
                        show_text(txt);
                        break;
                    }
                    this->inventory.delete_item(item);
                    this->closeInfo();
                    return;
                }
            }
        }
        this->closeInfo();
        return;
    }
    Consumable * tmp2 = dynamic_cast<Consumable *>(&(*item));
    if (tmp2 != nullptr)
    {
        item->showInfo();
        vector<string> choices = {"Back", "Use", "Drop"};
        vector<shared_ptr<Item> > showObjects = {item, item, item};
        Choicer choicer(choices);
        switch (choicer.ask_for_choice(showObjects))
        {
            case 0: this->closeInfo(); return;
            case 1:
            {
                this->actualHealth += tmp2->get_health();
                if (actualHealth > stats.health)
                    actualHealth = stats.health;
                char sometext[50];
                sprintf(sometext, "You used %s. Your health: %d/%d.", item->get_name().c_str(), actualHealth, stats.health);
                this->inventory.delete_item(item);
                vector<string> sometext2 = {string(sometext)};
                show_text(sometext2);
                break;
            }
            case 2: this->inventory.delete_item(item); break;
        }
        this->closeInfo();
        return;
    }

}

void Player::setCoords(int y, int x)
{
    this->actualPositionX = x;
    this->actualPositionY = y;
}

void Player::newGamePlayer()
{
    this->name = "meloun";
    this->experience = 0;
    this->inventory.size = 5;
    this->stats.health = 1000;
    this->actualHealth = 10;
    this->actualPositionX = 0;
    this->actualPositionY = 0;
    this->level = 1;
    this->stats.strenght = 4;
    Ability punch;
    punch.name = "punch";
    punch.strengthScale = 4;
    punch.timeNeeded = 3;
    punch.intScale = 0;
    this->abilities.push_back(punch);
    Ability kick;
    kick.name = "kick";
    kick.strengthScale = 1;
    kick.timeNeeded = 1;
    kick.intScale = 0;
    this->abilities.push_back(kick);
    this->alive = true;
    this->inventory.add_item(Equipable().randomItem(3, 2, 70));
    this->inventory.add_item(Consumable().randomItem(3, 3, 90));
    this->inventory.add_item(Equipable().randomItem(3, 0, 70));
    this->inventory.add_item(Equipable().randomItem(3, 6, 70));
    this->inventory.add_item(Consumable().randomItem(1, 1, 90));
    this->inventory.add_item(Consumable().randomItem(1, 2, 90));
    this->inventory.add_item(Consumable().randomItem(2, 2, 90));
}

void Player::add_experience(int exp)
{
    this->experience += exp;
}

std::vector<Ability> Player::get_abilities()
{
    return this->abilities;
}

Player::Player()
{
}

vector<shared_ptr<Item> > & Player::get_inventory()
{
    return this->inventory.items;
}

vector<shared_ptr<Item> > & Player::get_equip()
{
    return this->equipedItems;
}

bool Player::isAlive()
{
    return this->alive;
}

void Player::showInfo()
{
    char number[50] = {};
    this->infoWindow = newwin(SCREEN_HEIGHT, SCREEN_WIDTH, 0, 0);
    werase(infoWindow);
    box(infoWindow, 0, 0);
    mvwprintw(infoWindow, 1, (SCREEN_WIDTH - 2) / 2 - 6, "-- Player --");
    mvwprintw(infoWindow, 2, 1, "Name: ");
    wprintw(infoWindow, this->name.c_str());
    sprintf(number, " lvl %d", this->level);
    wprintw(infoWindow, number);
    mvwprintw(infoWindow, 4, 1, "Health: ");
    sprintf(number, "%d/%d", this->actualHealth, this->stats.health);
    wprintw(infoWindow, number);
    mvwprintw(infoWindow, 6, 1, "Stats: ");

    mvwprintw(infoWindow, 6, 8, "HP: ");
    sprintf(number, "\t%d", this->stats.health);
    wprintw(infoWindow, number);

    mvwprintw(infoWindow, 7, 8, "Deff: ");
    sprintf(number, "\t%d", this->stats.defence);
    wprintw(infoWindow, number);

    mvwprintw(infoWindow, 8, 8, "Str: ");
    sprintf(number, "\t%d", this->stats.strenght);
    wprintw(infoWindow, number);

    mvwprintw(infoWindow, 9, 8, "Int: ");
    sprintf(number, "\t%d", this->stats.inteligence);
    wprintw(infoWindow, number);
    
    mvwprintw(infoWindow, 11, 1, "Abilities: ");
    if (this->abilities.empty())
        wprintw(infoWindow, "none");
    else
        for (size_t i = 0; i < abilities.size(); ++i)
            mvwprintw(infoWindow, 11 + i, 12, abilities[i].name.c_str());

    wrefresh(infoWindow);
}
void Player::closeInfo()
{
    if (infoWindow == NULL)
        return;
    werase(infoWindow);
    wrefresh(infoWindow);
    delwin(infoWindow);
    infoWindow = NULL;
}

int Player::read(ifstream & file)
{
    if (!file.is_open())
        return 1;

    stats.read(file);
    file.read((char *) & actualHealth, sizeof(int));
    file.read((char *) & level, sizeof(int));
    file.read((char *) & alive, sizeof(bool));
    file.read((char *) & experience, sizeof(int));
    inventory.read(file);
    size_t tmp;
    file.read((char *) & tmp, sizeof(size_t));
    if (!file)
        return 1;
    for (size_t i = 0; i < tmp; ++i)
    {
        int typess;
        file.read((char *) & typess, sizeof(int));
        try
        {
            if (typess == 1)
                equipedItems.push_back(Equipable().read(file));
            else
                equipedItems.push_back(Consumable().read(file));
        }
        catch(const std::exception& e)
        {
            return 1;
        }
    }
    file.read((char *) & tmp, sizeof(size_t));
    if (!file)
        return 1;
    for (size_t i = 0; i < tmp; ++i)
    {
        try
        {
            abilities.push_back(Ability().read(file));
        }
        catch (const std::exception & e)
        {
            return 1;
        }
    }
    char tmpname[21];
    file.read((char *) & tmpname, sizeof(tmpname));
    name = string(tmpname);
    file.read((char *) & actualPositionX, sizeof(int));
    file.read((char *) & actualPositionY, sizeof(int));
    if (!file)
        return 1;
    return 0;
}
int Player::write(ofstream & file)
{
    if (!file.is_open())
        return 1;

    stats.write(file);
    file.write((char *) & actualHealth, sizeof(int));
    file.write((char *) & level, sizeof(int));
    file.write((char *) & alive, sizeof(bool));
    file.write((char *) & experience, sizeof(int));
    inventory.write(file);
    size_t tmp = equipedItems.size();
    file.write((char *) & tmp, sizeof(size_t));
    for (size_t i = 0; i < tmp; ++i)
        equipedItems[i]->write(file);
    tmp = abilities.size();
    file.write((char *) & tmp, sizeof(size_t));
    for (size_t i = 0; i < tmp; ++i)
        abilities[i].write(file);
    char tmpname[21];
    sprintf(tmpname, "%s", name.c_str());
    file.write((char *) & tmpname, sizeof(tmpname));
    file.write((char *) & actualPositionX, sizeof(int));
    file.write((char *) & actualPositionY, sizeof(int));
    return 0;
}