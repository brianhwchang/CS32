
// Game.h

#ifndef GAME_INCLUDED
#define GAME_INCLUDED

// You may add data members and other member functions to this class.
#include "Dungeon.h"
#include "Actor.h"

class Game
{
public:
    Game(int goblinSmellDistance);
    ~Game();
    void play();
    
    enum MOVE_TYPE {
        LEFT = 'h',
        RIGHT = 'l',
        UP = 'k',
        DOWN = 'j',
        OBJECT_PICK_UP = 'g',
        WIELD_WEAPON = 'w',
        READ_SCROLL = 'r',
        INVENTORY = 'i',
        DESCEND_STAIR = '>',
        QUIT = 'q',
        CHEAT = 'c',
    };
private:

    Dungeon* m_dungeon;
    Player* m_player;
};

#endif // GAME_INCLUDED
