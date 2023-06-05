#include "GameSession.h"

GameSession* GameSession::_GameSession{ nullptr };

GameSession::GameSession()
{
    StateGame = GameState::Menu;
    LastKeyPressDirection = PressKeysDirection::Up;
    ActualKeyPressDirection = PressKeysDirection::Up;
}

// The only one instance
GameSession* GameSession::GetInstance()
{
    if (_GameSession == nullptr)
    {
        _GameSession = new GameSession();
    }

    return _GameSession;
}

// Change state game
void GameSession::SetStateGame(GameState NewStateGame)
{
    StateGame = NewStateGame;
}

// Getting current state game
GameState GameSession::GetStateGame() const
{
    return StateGame;
}

// Collision check with the tail
bool GameSession::IsCollisionWithTail() const
{
    return _Player->IsCollisionWithTail(_Player->GetHeadCoordinate(), 1);
}

// Collision check with the border
bool GameSession::IsCollisionWithBorder() const
{
    /*
    * _Render->GetWindowWidth() - 1 = because '1' it is symbol of border
    * _Render->GetWindowHeight() - 2 = minus 1 symbol of border 
    *  & minus 1 - row for display score by player 
    */
     
    if (_Player->GetHeadCoordinate().first >= _Render->GetWindowWidth() - 1
        || _Player->GetHeadCoordinate().first == 0
        || _Player->GetHeadCoordinate().second >= _Render->GetWindowHeight() - 2
        || _Player->GetHeadCoordinate().second == 0)
    {
        return true;
    }

    return false;
}

void GameSession::ChangedCurrentKeyPress(PressKeysDirection NewValue)
{
    if (StateGame == GameState::Playing && _Player != nullptr)
    {
        switch (LastKeyPressDirection)
        {
            // Create new head for snake
            case Up:   _Player->PushHead(0,-1); break;
            case Down: _Player->PushHead(0,1); break;
            case Left: _Player->PushHead(-1,0); break;
            case Right:_Player->PushHead(1,0); break;
        }
    } 

    if (StateGame == GameState::Menu)
    {
        switch (LastKeyPressDirection)
        {
            case Up:   _MenuBar->NextSelect(-1); break;
            case Down: _MenuBar->NextSelect(1); break;
        }

        UpdateSelect();
    }
}

void GameSession::SetWindowSession(uint32_t WindowWidth, uint32_t WindowHeight)
{
    // Getting information about the size of the player's monitor
    uint16_t UserDisplayX = GetSystemMetrics(SM_CXSCREEN);;
    uint16_t UserDisplayY = GetSystemMetrics(SM_CYSCREEN);

    // Getting a pointer to the player's console and moving to center, resizing that console
    HWND Hwnd = GetConsoleWindow();
    MoveWindow(
        Hwnd,
        UserDisplayX / 2 - WindowWidth / 2,
        UserDisplayY / 2 - WindowHeight / 2,
        WindowWidth,
        WindowHeight,
        TRUE);

    // Getting size two-dimensional array characters from buffer console
    CONSOLE_SCREEN_BUFFER_INFO Csbi;
    uint32_t Columns, Rows;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Csbi);
    Columns = Csbi.srWindow.Right - Csbi.srWindow.Left + 1;
    Rows = Csbi.srWindow.Bottom - Csbi.srWindow.Top + 1;

    _Render->SetWindowWidth(Columns);
    _Render->SetWindowHeight(Rows);
}

void GameSession::SpawnFood()
{
    std::random_device dev;
    std::mt19937 rng(dev());

    while (true)
    {
        std::uniform_int_distribution<std::mt19937::result_type> RandomCoordX(1, _Render->GetWindowWidth() - 2);
        // Minus 3 - because of a row with the player's score
        std::uniform_int_distribution<std::mt19937::result_type> RandomCoordY(1, _Render->GetWindowHeight() - 3);

        
        // if the coordinates of the spawn coincide with the coordinates of the tail or head of the snake - generate again
        if (_Player->IsCollisionWithTail({ RandomCoordX(rng), RandomCoordY(rng)}) == true)
        {
            continue;
        }
        else
        {
            _Food->SetCoordinateObject(RandomCoordX(rng), RandomCoordY(rng));

            break;
        }
    }

    // Drew food on the map
    _Render->DrawObject2D(_Food->GetCoordinateObject().first, _Food->GetCoordinateObject().second, 'F');
}

void GameSession::HandleInput()
{
    while (true)
    {
        if (_kbhit())
        {
            Mutex.lock();

            // Critical zone!!!
            switch (_getch())
            {
            case 'a': case 'A': case KEY_LEFT:
            {
                if (ActualKeyPressDirection != PressKeysDirection::Right)
                {
                    LastKeyPressDirection = PressKeysDirection::Left;
                }

                break;
            }
            case 'd': case 'D': case KEY_RIGHT:
            {
                if (ActualKeyPressDirection != PressKeysDirection::Left)
                {
                    LastKeyPressDirection = PressKeysDirection::Right;
                }

                break;
            }
            case 's': case 'S': case KEY_DOWN:
            {
                if (StateGame == GameState::Menu)
                {
                    LastKeyPressDirection = PressKeysDirection::Down;

                    ChangedCurrentKeyPress(LastKeyPressDirection);
                }

                if (ActualKeyPressDirection != PressKeysDirection::Up)
                {
                    LastKeyPressDirection = PressKeysDirection::Down;
                }

                break;
            }
            case 'w': case 'W': case KEY_UP:
            {
                if (StateGame == GameState::Menu)
                {
                    LastKeyPressDirection = PressKeysDirection::Up;

                    ChangedCurrentKeyPress(LastKeyPressDirection);
                }

                if (ActualKeyPressDirection != PressKeysDirection::Down)
                {
                    LastKeyPressDirection = PressKeysDirection::Up;
                }

                break;
            }

            case KEY_RETURN: bIsEnterPressed = true; break;
            case KEY_ESCAPE: SetStateGame(GameState::Menu); break;
            }

            Mutex.unlock();

        }
    }
}

void GameSession::StartSession()
{
    while (true)
    {
        _Render->DrawMainMenu();

        // Maximum number of menu items
        _MenuBar->SetMaxSample(2);
        UpdateSelect();

        while(StateGame == GameState::Menu)
        {
            if (bIsEnterPressed == true)
            {
                switch (_MenuBar->GetCurrentSelection())
                {
                    case 0:
                    {
                        SetStateGame(GameState::Playing);

                        _Player = new Player();
                        _Food = new Food();

                        // Create first head for snake
                        _Player->PushHead((_Render->GetWindowWidth() - 2) / 2, (_Render->GetWindowHeight() - 2) / 2);

                        // Draw area & spawn food on map
                        _Render->DrawAreaForGame();
                        _Render->DrawObject2D(_Player->GetHeadCoordinate().first, _Player->GetHeadCoordinate().second, 'O');

                        SpawnFood();

                        GameLogic();

                        // Clear console and draw end screen
                        _Render->Cls();

                        _Render->DrawObject2D((_Render->GetWindowWidth() / 2) - 5, (_Render->GetWindowHeight() / 2) - 5, "Game Over");
                        _Render->DrawObject2D((_Render->GetWindowWidth() / 2) - 17, (_Render->GetWindowHeight() / 2) + 4, "Please press 'Enter' to be continue");

                        _Render->DrawScreenResult((_Render->GetWindowWidth() / 2) - 5, (_Render->GetWindowHeight() / 2) - 4, _Player->GetScore());

                        std::cin.ignore();

                        bIsEnterPressed = false;

                        delete _Player, _Food;

                        break;
                    }
                    case 1: _Render->Cls(); exit(0);
                }

                break;
            }

        }
      
    }
   
}



void GameSession::GameLogic()
{
    while (StateGame == Playing)
    {
        // Draw current head
        // Current result on monitor ->
        /*
        * * * * * * * * * * * * * * * * *
        *                               *
        *               o               *
        *                               *
        *                               *
        * * * * * * * * * * * * * * * * *
        */

        _Render->DrawObject2D(_Player->GetHeadCoordinate().first, _Player->GetHeadCoordinate().second, 'o');

        Mutex.lock();

        //Critical zone
        ActualKeyPressDirection = LastKeyPressDirection;

        // Change head
        ChangedCurrentKeyPress(ActualKeyPressDirection);

        Mutex.unlock();

        // Draw new head after pushing 
        // Current result on monitor ->
        /*
        * * * * * * * * * * * * * * * * *
        *                               *
        *               oO              *
        *                               *
        *                               *
        * * * * * * * * * * * * * * * * *
        */
        _Render->DrawObject2D(_Player->GetHeadCoordinate().first, _Player->GetHeadCoordinate().second, 'O');

        // Border collision check
        if (IsCollisionWithBorder() == true)
        {
            SetStateGame(GameState::Menu);

            break;
        }

        // Tail collision check
        if (IsCollisionWithTail() == true)
        {
            SetStateGame(GameState::Menu);

            break;
        }

        // Checking if the head is on the food
        if (_Player->GetHeadCoordinate() == _Food->GetCoordinateObject())
        {
            // In case you come across food - skip erasing and deleting
            // and adding score for player
            // Current result on monitor ->
            /*
            * * * * * * * * * * * * * * * * *
            *                               *
            *               oO              *
            *                               *
            *                               *
            * * * * * * * * * * * * * * * * *
            */
            _Player->AddScore(_Food->GetPrizeOfFood());

            SpawnFood();

        }
        else
        {
            // Erasing and removing the last "extra" element of the snake
            // Current result on monitor ->
            /*
            * * * * * * * * * * * * * * * * *
            *                               *
            *                O              *
            *                               *
            *                               *
            * * * * * * * * * * * * * * * * *
            */
            _Render->DrawObject2D(_Player->GetTailCoordinate().first, _Player->GetTailCoordinate().second, ' ');

            _Player->PopTail();
        }

        // Draw current score
        _Render->DrawScreenResult((_Render->GetWindowWidth() / 2) - 5, _Render->GetWindowHeight() - 1,_Player->GetScore());

        std::this_thread::sleep_for(std::chrono::milliseconds(_Player->GetSpeed()));     

    }
}

// Display of player selection depending on the value CurrentSelectionInMenu or LastSelection
// LastSelection - clear last select
// CurrentSelectionInMenu - draw mark `#` for current selection
void GameSession::UpdateSelect()
{
    switch (_MenuBar->GetLastSelection())
    {
        case 0:
        {
            _Render->DrawObject2D((_Render->GetWindowWidth() / 2) - 4, (_Render->GetWindowHeight() / 2) - 5, ' ');
            
            break;
        }
        case 1:
        {
            _Render->DrawObject2D((_Render->GetWindowWidth() / 2) - 4, (_Render->GetWindowHeight() / 2) - 4, ' ');
            
            break;
        }
    }

    switch (_MenuBar->GetCurrentSelection())
    {
        case 0:
        {
            _Render->DrawObject2D((_Render->GetWindowWidth() / 2) - 4, (_Render->GetWindowHeight() / 2) - 5, '#');
            
            break;
        }
        case 1:
        {
            _Render->DrawObject2D((_Render->GetWindowWidth() / 2) - 4, (_Render->GetWindowHeight() / 2) - 4, '#');
            
            break;
        }
    }
}

