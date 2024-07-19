#include "Field.h"
#include "Command.h"
#include <cmath>


Cell::Cell(int r, int c): row(r), column(c) {}

Deck::Deck(int r, int c, bool s): Cell(r, c), isShot(s) {}

const std::vector<Deck>& Ship::getDecks() const {
    return decks;
}

void Ship::push_back(const Deck& c) {
    decks.push_back(c);
}

bool Ship::checkCollision(const Ship& ship) const {
    for (const Cell& deck: decks) {
        for (const Cell& otherDeck: ship.getDecks()) {
            if(abs(deck.column - otherDeck.column) <= 1 && abs(deck.row - otherDeck.row) <= 1)
                return false;
        }
    }
    return true;
}

bool Ship::isAlive() const {
    return alive;
}

void Ship::updateStatus() {
    alive = false;
    for(Deck& dck: decks)
        if(!dck.isShot)
            alive = true;
}

std::shared_ptr<Command> Ship::hitCell(const Cell& pos) {
    for(Deck& dck: decks) {
        if(dck.row == pos.row && dck.column == pos.column) {
            if(dck.isShot)
                return std::shared_ptr<Command>(new MissCommand());
            else {
                dck.isShot = true;
                updateStatus();
                if (alive)
                    return std::shared_ptr<Command>(new HitCommand());
                return std::shared_ptr<Command>(new DestroyCommand());
            }
        }
    }
    return std::shared_ptr<Command>(new MissCommand());
}

void Ship::pushSurroundings(std::vector<Cell>& shots) const {
    for (const Deck& dck: decks) {
        for (int dr = -1; dr <= 1; ++dr) {
            for (int dc = -1; dc <= 1; ++dc) {
                Cell c(dck.row + dr, dck.column + dc);
                if(c.row >= 1 && c.row <= 10 && c.column >= 1 && c.column <= 10)
                    shots.push_back(c);
            }
        }
    }
}


const std::vector<Cell>& Field::getShots() const {
    return shots;
}
const std::vector<Ship>& Field::getShips() const {
    return ships;
}

std::shared_ptr<Command> Field::hitCell(const Cell& pos) {
    shots.push_back(pos);
    for(Ship& s: ships) {
        std::shared_ptr<Command> cmd = s.hitCell(pos);
        if (cmd->isMiss()) continue;
        if(!s.isAlive())
            s.pushSurroundings(shots);
        return cmd;
    }
    return std::shared_ptr<Command>(new MissCommand());
}

bool Field::tryToPlace(int row, int column, bool direction, int cntDecks) { //true, если удалось
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

bool Field::isAnyShipAlive() const {
    bool answer = false;
    for(const Ship& s: ships)
        answer = (answer || s.isAlive());
    return answer;
}

void Field::clear() {
    shots.clear();
    ships.clear();
}