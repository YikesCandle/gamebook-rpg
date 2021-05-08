#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <ncurses.h>
#include "gamedata.hpp"
#include "action.hpp"



class Game
{
    public:

         Game() = default;
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
        GameData Data;
};

#endif // GAME_H