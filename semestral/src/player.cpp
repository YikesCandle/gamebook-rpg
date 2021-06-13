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
            vector<shared_ptr<Item> > showObjects = {item, item};
            if (isItemEquiped(item))
                choices.push_back("Unequip");
            else
                choices.push_back("Equip");
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
        vector<string> choices = {"Back", "Use"};
        vector<shared_ptr<Item> > showObjects = {item, item};
        Choicer choicer(choices);
        switch (choicer.ask_for_choice(showObjects))
        {
            case 0: this->closeInfo(); return;
            case 1:
            {
                this->inventory.delete_item(item);
                this->actualHealth += tmp2->get_health();
                if (actualHealth > stats.health)
                    actualHealth = stats.health;
                char sometext[50];
                sprintf(sometext, "You used %s. Your health: %d/%d.", item->get_name().c_str(), actualHealth, stats.health);
                vector<string> sometext2 = {string(sometext)};
                show_text(sometext2);
            }
        }
        this->closeInfo();
        return;
    }

}

void Player::newGamePlayer()
{
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
    this->inventory.add_item(Consumable().randomItem(2, 2, 90));
    this->inventory.add_item(Equipable().randomItem(3, 0, 70));
    this->inventory.add_item(Consumable().randomItem(1, 1, 90));
    this->inventory.add_item(Consumable().randomItem(1, 2, 90));
    this->inventory.add_item(Consumable().randomItem(3, 3, 90));
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
    delete(infoWindow);
    infoWindow = NULL;
}