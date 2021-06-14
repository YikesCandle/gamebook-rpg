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
        int Create_character();
        void Show_story() const;
        void init_new_game_data();
        void init_load_game_data();

        // --- load game ---
        void Load_data();
        void SaveGame();
    
        // --- in game functions ---
        void LookAround();
        void OpenGear();
        void OpenInventory();
        void OpenMap();
        void OpenMenu();
        //void EvokeAction(const Action & action);
        void PlayerDead();

        // DATA
        bool running = false;
        bool playing = false;
        GameData Data;
};

#endif // GAME_H