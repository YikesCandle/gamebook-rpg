#include "headerFiles/action.hpp"


using namespace std;

Fight::Fight(const Enemy & enemy)
{
    this->enemy = enemy;
    this->type = "Fight";
}
void Fight::Evoke(Player & player)
{
    vector<string> startOfFightText = {this->enemy.startOfFight};
    show_text(startOfFightText);
    // fight
    WINDOW *fightWindow = newwin(SCREEN_HEIGHT - 2, SCREEN_WIDTH - 2, 1, 1);
    wclear(fightWindow);
    wrefresh(fightWindow);
    int playerAbilityTime = 0, enemyAbilityTime = 0;
    Ability playerAbility, enemyAbility;
    vector<string> lines;
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

            enemyAbility = this->enemy.abilities[rand() % (int)this->enemy.abilities.size()];
            enemyAbilityTime += enemyAbility.timeNeeded;
            sprintf(tmp, "Enemy is preparing an ability: %s (%d)", enemyAbility.name.c_str(), enemyAbility.timeNeeded);
            lines.push_back(string(tmp));

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
            sprintf(tmp, "You dealt %d damage while using %s ability. Enemy HP: %d/%d\0", damage, 
                                    playerAbility.name.c_str(), enemy.actualHealth, enemy.stats.health);
            lines.push_back(string(tmp));
            vector<string> choices;

            if ((int)lines.size() >= SCREEN_HEIGHT - 2)
            lines.erase(lines.begin(), lines.begin() + (int)lines.size() - SCREEN_HEIGHT + 2 + 1);
            werase(fightWindow);
            for (size_t i = 0; i < lines.size(); ++i)
                mvwprintw(fightWindow, i, 0, lines[i].c_str());
            wrefresh(fightWindow);

            for (const Ability & ability : player.get_abilities())
                choices.push_back(ability.name);
            Choicer menubar(choices);
            playerAbility = player.get_abilities()[menubar.ask_for_choice()];
            playerAbilityTime += playerAbility.timeNeeded;

            sprintf(tmp, "You are preparing an ability: %s (%d)", playerAbility.name.c_str(), playerAbility.timeNeeded);
            lines.push_back(string(tmp));
        }
        //enemy attack
        else
        {
            int damage = enemyAbility.calculateDmg(enemy.level, enemy.stats, player.stats);
            player.actualHealth -= damage;
            if (player.actualHealth < 0)
                player.actualHealth = 0;
            char tmp[100];
            sprintf(tmp, "Enemy dealt %d damage while using %s ability. Your HP: %d/%d", damage, 
                                    enemyAbility.name.c_str(), player.actualHealth, player.stats.health);
            lines.push_back(string(tmp));
            vector<string> choices;

            enemyAbility = this->enemy.abilities[rand() % (int)this->enemy.abilities.size()];
            enemyAbilityTime += enemyAbility.timeNeeded;
            sprintf(tmp, "Enemy is preparing an ability: %s (%d)", enemyAbility.name.c_str(), enemyAbility.timeNeeded);
            lines.push_back(string(tmp));
        }
        if ((int)lines.size() >= SCREEN_HEIGHT - 2)
            lines.erase(lines.begin(), lines.begin() + (int)lines.size() - SCREEN_HEIGHT + 2 + 1);
        
        werase(fightWindow);
        for (size_t i = 0; i < lines.size() + add; ++i)
            mvwprintw(fightWindow, i, 0, lines[i].c_str());
        wrefresh(fightWindow);
    }
    if (player.actualHealth < 0)
    {

    }
    if (enemy.actualHealth < 0)
    {

    }
    werase(fightWindow);
    wrefresh(fightWindow);
    delete(fightWindow);
}

std::string Action::get_type()
{
    return this->type;
}
void Action::Evoke(Player & player)
{

}