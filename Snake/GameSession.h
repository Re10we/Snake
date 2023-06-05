#pragma once
#include "Render.h"
#include "Player.h"
#include "Food.h"
#include "MenuBar.h"
#include <mutex>
#include <conio.h>
#include <random>


#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ESCAPE 27
#define KEY_RETURN 13

// States for controlling game
enum GameState
{
    Menu,
    Playing
};

enum PressKeysDirection 
{
    Up,
    Down,
    Left,
    Right
};

// The main class is designed according to the pattern singleton
// GameSession it`s class container for other classes by project
class GameSession
{
public:

    // Set up size & coord console window
    void SetWindowSession(uint32_t WindowWidth, uint32_t WindowHeight);

    // Main functions
    void StartSession();
    void SpawnFood();
    void HandleInput();
    void GameLogic();
    void UpdateSelect();

    // Collision check
    bool IsCollisionWithBorder() const;
    bool IsCollisionWithTail() const;

    // The only one instance
    static GameSession* GetInstance();

    // This class should not be assignable.
    GameSession(GameSession& other) = delete;
    void operator=(const GameSession&) = delete;

protected:

    GameSession();

    void ChangedCurrentKeyPress(PressKeysDirection NewValue);

    //Getter & Setter state game 
    void SetStateGame(GameState NewStateGame);
    GameState GetStateGame() const;

private:

    Player* _Player;
    Food* _Food;
    Render* _Render = new Render();
    MenuBar* _MenuBar = new MenuBar();

    static GameSession* _GameSession;
    std::mutex Mutex;

    GameState StateGame;

    bool bIsEnterPressed = false;

    // Variables are created to check the spamming of keys by the player
    PressKeysDirection LastKeyPressDirection;
    PressKeysDirection ActualKeyPressDirection;

};
