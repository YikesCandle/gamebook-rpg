#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <ncurses.h>
#include <vector>
#include <random>
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

        // --- load game ---
        void Load_data();
    
        // --- in game functions ---
        void LookAround();
        void Travel();
        void OpenInventory();
        void OpenMap() const;
        void OpenMenu() const;
        //void EvokeAction(const Action & action);

        // DATA
        bool running = false;
        bool playing = false;
        GameData Data;
};

#endif // GAME_H