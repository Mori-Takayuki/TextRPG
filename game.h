#ifndef GAME_H
#define GAME_H

#include <string>
#include "player.h"
#include "monster.h"

class Game {
public:
    Game();
    void start();

private:
    Player* player;
    int monsterIndex;
    Monster createNextMonster(int index);
    void battle(Monster& monster);
};

#endif // GAME_H
