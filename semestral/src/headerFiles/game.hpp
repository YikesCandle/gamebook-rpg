#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <ncurses.h>
#include <vector>
#include <random>
#include <cstring>
#include "gamedata.hpp"
#include "action.hpp"
#include "choicer.hpp"
#include "other.hpp"

// main class for the game, it controls every process in the game
class Game
{
    public:

        Game();
        ~Game() = default;
        
        // Starts the game, opens a main menu, prepares ncurses window
        // sets game.running to true
        void Start();

        // Ends the tame, deletes window, sets Game::running to false
        void End();

        // Starts main game loop -> sets Game::playing to true
        void Play();

    private:

        // prepares ncurses window, is called from game.Start method
        void Init();

        // --- new game ---

        // creating new-character proces (here only aks for name)
        int Create_character();

        // shows lore of the game
        void Show_story() const;

        // generates game.data (map, player), normally called after Game::Create_character method
        void init_new_game_data();

        // same as Game::init_new_game_data method, but Player is loaded from file
        void init_load_game_data();

        // --- load game ---

        // does nothing
        void Load_data();

        // saves the actual game to file, rewrites old content (only one save at the time is possible)
        void SaveGame();
    
        // --- in game functions ---

        // shows accesible actions for the player at the current location
        void LookAround();

        // shows player into and qeuiped items (only equiped items)
        void OpenGear();

        // shows players inventory (all items)
        void OpenInventory();

        // shows current location info
        void OpenMap();

        // goes back to menu, unsaved progess wont be saved
        void OpenMenu();

        // this method is called, when player dies -> shows message, ends the game
        void PlayerDead();

        // DATA

        // between Game::Start and Game::End true, else false
        bool running = false;

        // only true after Game::Play
        bool playing = false;

        // contains Map and Player data
        GameData Data;
};

#endif // GAME_H