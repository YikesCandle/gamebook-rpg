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
                if (this->Create_character())
                    continue;
                this->init_new_game_data();
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
        vector<string> choices = {"look around", "travel", "open inventar", "open map", "menu"};
        Choicer actions(choices);
        int select = actions.ask_for_choice();
        switch(select)
        {
            case 0: this->LookAround();     break;
            case 1: this->Travel();         break;
            case 2: this->OpenInventory();  break;
            case 3: this->OpenMap();        break;
            case 4: this->OpenMenu();       break;
        }
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
    werase(characterWindow);
    wrefresh(characterWindow);
    delete(characterWindow);
    this->Data.player.set_name(string(name));
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
    this->Data.player.newGamePlayer();
    this->Data.map.newGameMap();
}
void Game::LookAround()
{
    vector<string> choices;
    for (auto & action : Data.getCurrentLocation().avaliableActions)
        choices.push_back(action->get_type());
    if (choices.size() == 0)
        exit(1);
    Choicer choicer(choices);
    Data.getCurrentLocation().avaliableActions[choicer.ask_for_choice()]->Evoke(this->Data.player);
}
void Game::Travel()
{
    
}
void Game::OpenInventory()
{
    
}
void Game::OpenMap() const
{
    
}
void Game::OpenMenu() const
{
    
}