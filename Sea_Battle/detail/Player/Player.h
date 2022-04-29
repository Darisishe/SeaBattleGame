#ifndef PLAYER_H
#define PLAYER_H
#include "Field.h"

class Player {
    std::string name;
    std::string password;
public:
    Field field;
    Player();
    Player(const std::string& name, const std::string& password);
    const std::string& getName() const;
    bool checkPassword(const std::string&) const;
};


#endif
