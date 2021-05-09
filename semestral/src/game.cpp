#include "game.hpp"

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
    Choicer mainManu("New Game", "Load Game", "Quit Game");
    while (this->running)
    {
        int select = mainManu.ask_for_choice();
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
    Choicer actions("rozlédnou se po oblasi", "cestovat", "otevřít inventář", "prohlédout mapu", "menu");
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