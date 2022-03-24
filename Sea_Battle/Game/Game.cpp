#include "Game.h"
#include "Command.h"
Game::Game(const InterfaceIO& io): IO(io) {
    IO.initializePlayers(player1, player2);
};
void Game::makeTurns(Player& current, Player& other) {
    IO.logIn(current);
    Cell pos = IO.askAttackPosition(current, other);
    std::shared_ptr<Command> cmd = other.attack(pos);
    while (!cmd->isMiss() && other.isAlive()) {
        cmd->execute(IO);
        pos = IO.askAttackPosition(current, other);
        cmd = other.attack(pos);
    }
    cmd->execute(IO);
}
void Game::play() {
    bool proceed = true;
    while(proceed) {
        IO.arrangeShips(player1);
        IO.arrangeShips(player2);
        while(player1.isAlive() && player2.isAlive()) {
            makeTurns(player1, player2);
            if(player2.isAlive())
                makeTurns(player2, player1);
        }
        IO.congratulate(player1.isAlive() ? player1 : player2);
        player1.clear();
        player2.clear();
        proceed = IO.suggestNewGame();
    }
}