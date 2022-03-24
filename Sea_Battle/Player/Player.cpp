#include "Player.h"
#include "Command.h"

Player::Player(){}

Player::Player(const std::string& nm, const std::string& pas): name(nm), password(pas) {}

const vector<Cell>& Player::getShots() const {
    return shots;
}

const vector<Ship>& Player::getShips() const {
    return ships;
}

const std::string& Player::getName() const {
    return name;
}

bool Player::checkPassword(const std::string& s) const {
    return s == password;
}

bool Player::tryToPlace(int row, int column, bool direction, int cntDecks) { //true, если удалось
    Ship potentialShip;
    while(cntDecks > 0) {
        if(row > 10 || column > 10) return false;
        potentialShip.push_back(Deck(row,column));
        if (direction) ++row;
        else ++column;
        --cntDecks;
    }
    for(Ship& ship: ships)
        if(!potentialShip.checkCollision(ship)) return false;
    ships.push_back(potentialShip);
    return true;
}

bool Player::isAlive() const {
    bool answer = false;
    for(const Ship& s: ships)
        answer = (answer || s.isAlive());
    return answer;
}

std::shared_ptr<Command> Player::attack(const Cell& pos) {
    shots.push_back(pos);
    for(Ship& s: ships) {
        std::shared_ptr<Command> cmd = s.attack(pos);
        if (cmd->isMiss()) continue;
        if(!s.isAlive())
            s.pushSurroundings(shots);
        return cmd;
    }
    return std::shared_ptr<Command>(new MissCommand());
}

void Player::clear() {
    shots.clear();
    ships.clear();
}
