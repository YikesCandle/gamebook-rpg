#include "game.hpp"

using namespace std;

void Game::Init()
{
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, true);
}

void Game::Play()
{
   this->Init();

   while (true)
   {
       
   }
}