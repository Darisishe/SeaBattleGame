#include "Game.h"
#include "Command.h"

Game::Game(const InterfaceIO& io): IO(io) {
    IO.initializePlayers(player1, player2);
}

void Game::makeTurns(Player& current, Player& other) {
    IO.logIn(current);
    Cell pos = IO.askAttackPosition(current, other);
    std::shared_ptr<Command> cmd = other.field.hitCell(pos);
    while (!cmd->isMiss() && other.field.isAnyShipAlive()) {
        cmd->execute(IO);
        pos = IO.askAttackPosition(current, other);
        cmd = other.field.hitCell(pos);
    }
    cmd->execute(IO);
}

void Game::play() {
    bool proceed = true;
    while(proceed) {
        IO.arrangeShips(player1);
        IO.arrangeShips(player2);
        while(player1.field.isAnyShipAlive() && player2.field.isAnyShipAlive()) {
            makeTurns(player1, player2);
            if(player2.field.isAnyShipAlive())
                makeTurns(player2, player1);
        }
        IO.congratulate(player1.field.isAnyShipAlive() ? player1 : player2);
        player1.field.clear();
        player2.field.clear();
        proceed = IO.suggestNewGame();
    }
}