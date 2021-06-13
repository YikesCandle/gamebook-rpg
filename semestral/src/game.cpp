#include "headerFiles/game.hpp"

using namespace std;

Game::Game()
{
}
void Game::Init()
{
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, true);
}
void Game::End()
{
    endwin();
    this->running = false;
}
void Game::Start()
{
    this->running = true;
    this->Init();
    while (this->running)
    {
        vector<string> choices = {"New Game", "Load Game", "Quit Game"};
        Choicer mainMenu(choices);
        int select = mainMenu.ask_for_choice();
        switch(select)
        {
            case 0:
                this->init_new_game_data();
                if (this->Create_character())
                    continue;
                this->Show_story();
            case 1:
                this->Play();
                break;
            case 2:
                this->End();
        }
    }
}
void Game::Play()
{
    this->playing = true;
    // gameloop
    while (this->playing)
    {
        vector<string> choices = {"look around", "You", "open inventar", "open map", "save", "menu"};
        Choicer actions(choices);
        int select = actions.ask_for_choice();
        switch(select)
        {
            case 0: this->LookAround();     break;
            case 1: this->OpenGear();       break;
            case 2: this->OpenInventory();  break;
            case 3: this->OpenMap();        break;
            case 4: this->SaveGame();       break;
            case 5: this->OpenMenu();       break;
        }
        if (!this->Data.player.isAlive())
            this->PlayerDead();
    }
}

// todo
int Game::Create_character()
{
    WINDOW *characterWindow = newwin(SCREEN_HEIGHT, SCREEN_WIDTH, 0, 0);
    box(characterWindow, 0, 0);

    mvwprintw(characterWindow, 1, 1, "Create character");
    mvwprintw(characterWindow, 4, 1, "name:");
    wrefresh(characterWindow);
    wmove(characterWindow, 4, 7);
    echo();
    curs_set(1);
    char name[20];
    wgetnstr(characterWindow, name, 20 * sizeof(char));
    curs_set(0);
    noecho();

    mvwprintw(characterWindow, 4, 1, "Hello ");
    mvwprintw(characterWindow, 4, 7, name);
    mvwprintw(characterWindow, 4, 7 + strlen(name), ", do you want to continue?");
    wrefresh(characterWindow);
    vector<string> chioces = {"Yes", "No"};
    Choicer choicer(chioces);
    switch(choicer.ask_for_choice())
    {
        case 0: break;
        case 1:
            werase(characterWindow);
            wrefresh(characterWindow);
            delete(characterWindow);
            return 1;
    }
    this->Data.player.set_name(string(name));
    werase(characterWindow);
    wrefresh(characterWindow);
    delete(characterWindow);
    return 0;
}
void Game::Show_story() const
{
    vector<string> story = {"This time, I was wondering if the cloud is enough for me. Do you understand?", "ale to nebylo tolik na to", "this is the end of the story enjoy"};
    show_text(story);
}
void Game::Load_data()
{
    
}
void Game::init_new_game_data()
{
    this->Data = GameData();
    this->Data.player.newGamePlayer();
    this->Data.map.newGameMap();
}
void Game::LookAround()
{
    vector<string> choices;
    choices.push_back("Back");
    for (auto & action : Data.getCurrentLocation().avaliableActions)
        choices.push_back(action->get_type());

    vector<shared_ptr<Action> > showObjects = Data.getCurrentLocation().avaliableActions;
    showObjects.insert(showObjects.begin(), make_shared<Action>(Action()));
    Choicer choicer(choices);
    int chosen = choicer.ask_for_choice(showObjects);
    if (chosen == 0)
        return;
    else
    {
        Data.getCurrentLocation().avaliableActions[chosen - 1]->Evoke(this->Data.player);
        if (!Data.getCurrentLocation().avaliableActions[chosen - 1]->isRepeatable())
            Data.getCurrentLocation().avaliableActions.erase(Data.getCurrentLocation().avaliableActions.begin() + chosen - 1);
    }
}
void Game::OpenGear()
{
    while (true)
    {
        vector<string> choices = {"Back", "Gear"};
        Choicer choicer(choices);
        vector<Player*> showObjects = {&this->Data.player, &this->Data.player};

        switch (choicer.ask_for_choice(showObjects))
        {
            case 0: return;
            case 1:
            {
                int lock = true;
                while (lock)
                {
                    vector<string> choicesItems;
                    choicesItems.push_back("Back");
                    for (auto item : Data.player.get_equip())
                        choicesItems.push_back(item->get_name());
                    vector<shared_ptr<Item> > showObjects = Data.player.get_equip();
                    showObjects.insert(showObjects.begin(), make_shared<Item>(Item()));
                    Choicer choicerItems(choicesItems);
                    int chosen = choicerItems.ask_for_choice(showObjects);
                    if (chosen == 0)
                        lock = false;
                    else
                        Data.player.itemManipulate(Data.player.get_equip()[chosen - 1]);
                }
            }
        }
    }
}
void Game::OpenInventory()
{
    while (true)
    {
        vector<string> choices;
        choices.push_back("Back");
        for (auto item : Data.player.get_inventory())
            choices.push_back(item->get_name());
        vector<shared_ptr<Item> > showObjects = Data.player.get_inventory();
        showObjects.insert(showObjects.begin(), make_shared<Item>(Item()));
        Choicer choicer(choices);
        int chosen = choicer.ask_for_choice(showObjects);
        if (chosen == 0)
            return;
        else
            Data.player.itemManipulate(Data.player.get_inventory()[chosen - 1]);
    }
}
void Game::OpenMap()
{
    vector<string> text = {"This function is not available.", "Yet..."};
    show_text(text);
}
void Game::OpenMenu()
{
    this->playing = false;
}
void Game::SaveGame()
{
    vector<string> text = {"This function is not available.", "Yet..."};
    show_text(text);
}

void Game::PlayerDead()
{
    vector<string> text = {"You way is ending right here. You ARE ...", "Dead... Better luck next tine."};
    show_text(text);
    playing = false;
}