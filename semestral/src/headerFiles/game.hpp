#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <ncurses.h>
#include <vector>
#include "gamedata.hpp"
#include "action.hpp"
#include "choicer.hpp"


static const int SCREEN_WIDTH = 60;
static const int SCREEN_HEIGHT = 15;

class Game
{
    public:

        Game();
        ~Game() = default;

        void Start();
        void End();
        void Play();

    private:

        void Init();
        // --- new game ---
        void Create_character();
        void Show_story() const;

        // --- load game ---
        void Load_data();
    
        // --- in game functions ---
        void LookAround();
        void Travel();
        void OpenInventory();
        void OpenMap() const;
        void OpenMenu() const;
        void EvokeAction(const Action & action);

        // DATA
        bool running = false;
        bool playing = false;
        WINDOW * window;
        GameData Data;
};

#endif // GAME_H