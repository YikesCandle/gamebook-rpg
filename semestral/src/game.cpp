#include "headerFiles/game.hpp"

using namespace std;

Game::Game()
: window(newwin(SCREEN_HEIGHT, SCREEN_WIDTH, 0, 0))
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
    vector<string> choices = {"New Game", "Load Game", "Quit Game", "Test1", "Test2", "Test3", "Test4", "Test5"};
    Choicer mainMenu(choices);
    while (this->running)
    {
        int select = mainMenu.ask_for_choice();
        switch(select)
        {
            case 0:
                this->Create_character();
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
    vector<string> choices = {"look around", "travel", "open inventar", "open map", "menu"};
    Choicer actions(choices);
    this->playing = true;
    // gameloop
    while (this->playing)
    {
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
void Game::Create_character()
{

}
void Game::Show_story() const
{
    
}
void Game::Load_data()
{
    
}
void Game::LookAround()
{
    
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
void Game::EvokeAction(const Action & action)
{
    
}