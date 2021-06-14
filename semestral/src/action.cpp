#include "headerFiles/action.hpp"


using namespace std;

Fight::Fight(const Enemy & enemy)
{
    this->enemy = enemy;
    this->type = "Fight";
}

bool Action::isRepeatable()
{
    return this->repeatable;
}
void Fight::Evoke(Player & player)
{
    vector<string> startOfFightText = {this->enemy.startOfFight};
    show_text(startOfFightText);
    // fight
    WINDOW *fightWindow = newwin(SCREEN_HEIGHT, SCREEN_WIDTH, 0, 0);
    wclear(fightWindow);
    wrefresh(fightWindow);
    int playerAbilityTime = 0, enemyAbilityTime = 0;
    Ability playerAbility, enemyAbility;
    vector<string> lines;
    pausePrint(lines, fightWindow, player.actualHealth, player.stats.health, enemy.actualHealth, enemy.stats.health);
    while (player.actualHealth > 0 && enemy.actualHealth > 0)
    {
        if (playerAbilityTime == 0 && enemyAbilityTime == 0)
        {
            vector<string> choices;
            for (const Ability & ability : player.get_abilities())
                choices.push_back(ability.name);
            Choicer menubar(choices);
            playerAbility = player.get_abilities()[menubar.ask_for_choice()];
            playerAbilityTime += playerAbility.timeNeeded;
            char tmp[100];
            sprintf(tmp, "You are preparing an ability: %s (%d)", playerAbility.name.c_str(), playerAbility.timeNeeded);
            lines.push_back(string(tmp));
            usleep(500000);
            pausePrint(lines, fightWindow, player.actualHealth, player.stats.health, enemy.actualHealth, enemy.stats.health);
            

            enemyAbility = this->enemy.abilities[rand() % (int)this->enemy.abilities.size()];
            enemyAbilityTime += enemyAbility.timeNeeded;
            sprintf(tmp, "Enemy is preparing an ability: %s (%d)", enemyAbility.name.c_str(), enemyAbility.timeNeeded);
            lines.push_back(string(tmp));
            usleep(500000);
            pausePrint(lines, fightWindow, player.actualHealth, player.stats.health, enemy.actualHealth, enemy.stats.health);
            continue;
        }
        //player attack
        if (playerAbilityTime <= enemyAbilityTime)
        {
            int damage = playerAbility.calculateDmg(player.level, player.stats, enemy.stats);
            enemy.actualHealth -= damage;
            if (enemy.actualHealth < 0)
                enemy.actualHealth = 0;
            char tmp[100];
            sprintf(tmp, "(%d) You dealt %d damage.", playerAbilityTime, damage);
            lines.push_back(string(tmp));
            usleep(500000);
            pausePrint(lines, fightWindow, player.actualHealth, player.stats.health, enemy.actualHealth, enemy.stats.health);
            vector<string> choices;

            if (enemy.actualHealth == 0)
                break;

            for (const Ability & ability : player.get_abilities())
                choices.push_back(ability.name);
            Choicer menubar(choices);
            playerAbility = player.get_abilities()[menubar.ask_for_choice()];
            playerAbilityTime += playerAbility.timeNeeded;

            sprintf(tmp, "You are preparing an ability: %s (%d)", playerAbility.name.c_str(), playerAbilityTime);
            lines.push_back(string(tmp));
            usleep(500000);
            pausePrint(lines, fightWindow, player.actualHealth, player.stats.health, enemy.actualHealth, enemy.stats.health);
        }
        //enemy attack
        else
        {
            int damage = enemyAbility.calculateDmg(enemy.level, enemy.stats, player.stats);
            player.actualHealth -= damage;
            if (player.actualHealth <= 0)
                player.actualHealth = 0;
            char tmp[100];
            sprintf(tmp, "(%d) Enemy dealt %d damage.", enemyAbilityTime, damage);
            lines.push_back(string(tmp));
            usleep(500000);
            pausePrint(lines, fightWindow, player.actualHealth, player.stats.health, enemy.actualHealth, enemy.stats.health);

            vector<string> choices;
            enemyAbility = this->enemy.abilities[rand() % (int)this->enemy.abilities.size()];
            enemyAbilityTime += enemyAbility.timeNeeded;
            sprintf(tmp, "Enemy is preparing an ability: %s (%d)", enemyAbility.name.c_str(), enemyAbilityTime);
            lines.push_back(string(tmp));
            usleep(500000);
            pausePrint(lines, fightWindow, player.actualHealth, player.stats.health, enemy.actualHealth, enemy.stats.health);
        }
    }
    vector<string> menu = {"End"};
    Choicer menubar(menu);
    menubar.ask_for_choice();

    pausePrint(lines, fightWindow, player.actualHealth, player.stats.health, enemy.actualHealth, enemy.stats.health);
    if (player.actualHealth <= 0)
    {
        werase(fightWindow);
        wrefresh(fightWindow);
        delwin(fightWindow);
        vector<string> text = {"You lost the fight and were killed. RIP."};
        show_text(text);
        player.alive = false;
        return;
    }
    if (enemy.actualHealth <= 0)
    {
        werase(fightWindow);
        wrefresh(fightWindow);
        delwin(fightWindow);

        vector<string> text;
        text.push_back("Congratulations! You won the fight.");
        char tmp[100] = {};

        sprintf(tmp, "EXP earned: %d", enemy.experience);
        text.push_back(string(tmp));
        player.add_experience(enemy.experience);
        vector<shared_ptr<Item> > drops = enemy.drops;
        for (size_t i = 0; i < drops.size(); ++i)
        {
            sprintf(tmp, "Item earned: %s lvl %d", drops[i]->get_name().c_str(), drops[i]->get_level());
            text.push_back(string(tmp));
            player.inventory.add_item(drops[i]);
        }
        show_text(text);
        double newLevel = (sqrt(2*(double)player.experience + 25) - 5) / 10.0;
        int nl = newLevel + 1;

        if (nl > player.level)
        {
            Stats addStats;
            addStats.defence = nl - player.level;
            addStats.strenght = nl - player.level;
            addStats.health = (nl - player.level) * nl + 100;
            addStats.inteligence = nl - player.level;
            player.stats += addStats;
            player.level = nl;
            char tmptmp[100];
            sprintf(tmptmp, "You leveled up! You stats went up. Your level: %d", nl);
            vector<string> tmptmptmpt = {string(tmptmp)};
            show_text(tmptmptmpt);
        }
    }
}

std::string Action::get_type()
{
    return this->type;
}
void Action::Evoke(Player & player)
{

}

void Action::showInfo()
{

}

void Action::closeInfo()
{

}

void Fight::showInfo()
{
    this->enemy.showInfo();
}
void Fight::closeInfo()
{
    this->enemy.closeInfo();
}

void Fight::pausePrint(vector<string> & lines, WINDOW * fightWindow, int p1, int p2, int e1, int e2)
{
    werase(fightWindow);
    if ((int)lines.size() >= SCREEN_HEIGHT - 3)
    lines.erase(lines.begin(), lines.begin() + (int)lines.size() - SCREEN_HEIGHT + 3 + 1);
    for (size_t i = 0; i < lines.size(); ++i)
        mvwprintw(fightWindow, i + 1, 0 + 1, lines[i].c_str());
    
    char pHp[(SCREEN_WIDTH - 2) / 2] = {};
    char eHp[(SCREEN_WIDTH - 2) / 2] = {};
    sprintf(pHp, "You: %d/%d", p1, p2);
    sprintf(eHp, "Enemy: %d/%d", e1, e2);
    mvwprintw(fightWindow, SCREEN_HEIGHT - 3 + 1, 0 + 1, pHp);
    mvwprintw(fightWindow, SCREEN_HEIGHT - 3 + 1, SCREEN_WIDTH - 3 - strlen(eHp) + 1, eHp);
    box(fightWindow, 0, 0);
    wrefresh(fightWindow);
}

void Location::showInfo()
{
    
    char number[40] = {};
    this->locationWindow = newwin(SCREEN_HEIGHT, SCREEN_WIDTH, 0, 0);
    werase(locationWindow);
    box(locationWindow, 0, 0);
    mvwprintw(locationWindow, 0, (SCREEN_WIDTH - 2) / 2 - 7, "-- Location --");
    mvwprintw(locationWindow, 2, 1, "Type: ");
    wprintw(locationWindow, this->type.c_str());
    sprintf(number, " lvl %d", this->level);
    wprintw(locationWindow, number);
    mvwprintw(locationWindow, 4, 1, "Coords: ");
    sprintf(number, "y: %d x: %d", this->y, this->x);
    wprintw(locationWindow, number);
    for (int i = 0; i < 16; ++i)
    for (int j = 0; j < 16; ++j)
    {
        if (i == this->y && j == this->x)
            mvwprintw(locationWindow, i + 1, j*2 + 25 , "O ");
        else
            mvwprintw(locationWindow, i + 1, j*2 + 25 , ". ");
    }
    wrefresh(locationWindow);
}
void Location::closeInfo()
{
    if (locationWindow == NULL)
        return;
    werase(locationWindow);
    wrefresh(locationWindow);
    delwin(locationWindow);
    locationWindow = NULL;
}

void Travel::Evoke(Player & player)
{
    if (rand() % 3 == 0)
    {
        Fight(Enemy().randomEnemy(this->location.level, rand() % 5)).Evoke(player);
        if (!player.isAlive())
            return;
    }
    vector<string> text = {"Travel to another location was successful!"};
    show_text(text);
    player.setCoords(this->location.y, this->location.x);
}
Travel::Travel(Location & local)
{
    this->repeatable = true;
    this->type = "Travel";
    this->location = local;
}
void Travel::showInfo()
{
    this->location.showInfo();
}
void Travel::closeInfo()
{
    this->location.closeInfo();
}
