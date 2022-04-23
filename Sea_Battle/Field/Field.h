#ifndef SEA_BATTLE_FIELD_H
#define SEA_BATTLE_FIELD_H

#include <vector>
#include <memory>

class Command;
struct Cell {
    int row;
    int column;
    Cell(int r, int c);
};

struct Deck: Cell {
    bool isShot = false;
    Deck(int r, int c, bool s = false);
};

class Ship {
    std::vector<Deck> decks;
    bool alive = true;
public:
    const std::vector<Deck>& getDecks() const;
    void push_back(const Deck& c);
    bool checkCollision(const Ship& ship) const;
    bool isAlive() const;
    void updateStatus();
    std::shared_ptr<Command> attack(const Cell& pos);
    void pushSurroundings(std::vector<Cell>& shots) const;
};

class Field {
    std::vector<Cell> shots;
    std::vector<Ship> ships;
public:
    const std::vector<Cell>& getShots() const;
    const std::vector<Ship>& getShips() const;
    std::shared_ptr<Command> attack(const Cell& pos);
    bool tryToPlace(int row, int column, bool direction, int cntDecks);
    bool isAlive() const;
    void clear();
};
#endif //SEA_BATTLE_FIELD_H
