#ifndef IO_H
#define IO_H
#include <string>
#include <vector>
class Player;
class Cell;
class InterfaceIO {
public:
    virtual void initializePlayers(Player& player1, Player& player2) const = 0;
    virtual void logIn(const Player&) const = 0;
    virtual void arrangeShips(Player& player) const = 0;
    virtual Cell askAttackPosition(const Player&, const Player&) const = 0;
    virtual void destroyMessage() const = 0;
    virtual void hitMessage() const = 0;
    virtual void missMessage() const = 0;
    virtual void congratulate(const Player&) const = 0;
    virtual bool suggestNewGame() const = 0;
};

class ConsoleIO: public InterfaceIO {
private:
    const std::string red = "\033[31m";
    const std::string blue = "\033[34m";
    const std::string reset = "\033[0m";
    const std::string clear = "\033[2J";
public:
    void drawField(const Player& player, char defaultForDeck = ' ') const;
    void draw(const Player& current, const Player& other) const;
    void registration(Player& player, int num) const;
    std::string nameOfShip(int cntDecks) const;
    void readPlacement(int& row, int& column, char& direction, bool withDirection) const;
    void initializePlayers(Player& player1, Player& player2) const override;
    void logIn(const Player& player) const override;
    void arrangeShips(Player& player) const override;
    Cell askAttackPosition(const Player& current, const Player& other) const override;
    void destroyMessage() const override;
    void hitMessage() const override;
    void missMessage() const override;
    void congratulate(const Player& winner) const override;
    bool suggestNewGame() const override;
};
#endif
