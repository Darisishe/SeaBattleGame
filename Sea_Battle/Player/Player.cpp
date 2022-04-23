#include "Player.h"

Player::Player(){}

Player::Player(const std::string& nm, const std::string& pas): name(nm), password(pas) {}

const std::string& Player::getName() const {
    return name;
}

bool Player::checkPassword(const std::string& s) const {
    return s == password;
}