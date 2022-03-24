#include "Ship.h"
#include "Command.h"

Cell::Cell(int r, int c): row(r), column(c) {}

Deck::Deck(int r, int c, bool s): Cell(r, c), isShot(s) {}

const vector<Deck>& Ship::getDecks() const {
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
std::shared_ptr<Command> Ship::attack(const Cell& pos) {
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
void Ship::pushSurroundings(vector<Cell>& shots) const {
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