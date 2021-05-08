#include "game.hpp"

using namespace std;
void Game::main_menu()
{
    cout << "1: NEW  GAME" << endl; 
    cout << "2: LOAD GAME" << endl;
    cout << "3: QUIT GAME" << endl;

    int input;
    cout << '> ';
    if (! (cin >> input) || input < 1 || input > 3)
    {
        cin.clear();
        cin.ignore(10000);
        cout << "Chyba. Zvolte '1' pro NEW, '2' pro LOAD, nebo '3' pro QUIT." << endl;
    }
    switch (input)
    {
    case 1: this-> new_game(); break;
    case 2: this->load_game(); break;
    case 3: this->quit_game(); break;
    }
}