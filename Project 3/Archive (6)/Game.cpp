// Game.cpp

#include "Game.h"
#include "utilities.h"
#include <iostream>
using namespace std;

// Implement these and other Game member functions you may have added.

Game::Game(int goblinSmellDistance)
{
    m_dungeon = new Dungeon();
}

Game::~Game()
{
    delete m_dungeon;
}

void Game::play()
{
    char move = 0;
    while (move != 'q')
    {
        // Display the board
        m_dungeon->printDungeon();
        // If player is dead
        if (m_dungeon->getPlayer()->isDead())
        {
            char move = 0;
            while (1)
            {
                move = getCharacter();
                if (move == 'q')
                {
                    return;
                }
                continue;
            }
        }
        // Get the current input by user
        move = getCharacter();
        
        // Process input
        switch(move) {
            case ARROW_UP:
            case ARROW_LEFT:
            case ARROW_RIGHT:
            case ARROW_DOWN:
                m_dungeon->setCurrentMove(move);
                // TODO: might be better to use this "playMove" function for all of the rest of the actions,
                // for now, just leave like this
                m_dungeon->playMove();
                break;
            case OBJECT_PICK_UP:
                m_dungeon->getPlayer()->pickUp();
                break;
            case WIELD_WEAPON:
                
            case READ_SCROLL:
                
            case INVENTORY:
                m_dungeon->getPlayer()->openIventory();
                break;
            case DESCEND_STAIR:
                m_dungeon->getPlayer()->descend();
                break;
            case QUIT:
                return;
            case CHEAT:
                m_dungeon->getPlayer()->cheat();
                break;
            default:
                // TODO: error handling?
                continue;
                
        }
        clearScreen();
            
    }
}

// You will presumably add to this project other .h/.cpp files for the
// various classes of objects you need to play the game:  player, monsters,
// weapons, etc.  You might have a separate .h/.cpp pair for each class
// (e.g., Player.h, Boegeyman.h, etc.), or you might put the class
// declarations for all actors in Actor.h, all game objects in GameObject.h,
// etc.
