#ifndef GAME_H
#define GAME_H

#include "IO.h"
#include "Player.h"

class Game {
    const InterfaceIO& IO;
    Player player1;
    Player player2;
public:
    Game(const InterfaceIO& io);
    void makeTurns(Player& current, Player& other);
    void play();
};
#endif
