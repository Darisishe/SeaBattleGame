#ifndef PLAYER_H
#define PLAYER_H
#include "Ship.h"
class Player {
    vector<Cell> shots;
    vector<Ship> ships;
    std::string name;
    std::string password;
public:
    Player();
    Player(const std::string&, const std::string&);
    const vector<Cell>& getShots() const;
    const vector<Ship>& getShips() const;
    const std::string& getName() const;
    bool checkPassword(const std::string&) const;
    bool tryToPlace(int row, int column, bool direction, int cntDecks);
    bool isAlive() const;
    std::shared_ptr<Command> attack(const Cell& pos);
    void clear();
};


#endif
