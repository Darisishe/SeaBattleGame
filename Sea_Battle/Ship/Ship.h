#ifndef SHIP_H
#define SHIP_H
#include <vector>
#include <memory>
using std::vector;
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
    vector<Deck> decks;
    bool alive = true;
public:
    const vector<Deck>& getDecks() const;
    void push_back(const Deck& c);
    bool checkCollision(const Ship& ship) const;
    bool isAlive() const;
    void updateStatus();
    std::shared_ptr<Command> attack(const Cell& pos);
    void pushSurroundings(vector<Cell>& shots) const;
};


#endif
