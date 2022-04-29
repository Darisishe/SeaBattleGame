#include <iostream>
#include <limits>
#include "IO.h"
#include "Player.h"

using std::vector;
void ConsoleIO::drawField(const Player& player, char defaultForDeck) const {
    vector<std::string> field(13);
    field[0] = "     A B C D E F G H I J";
    field[1] = "   ._____________________.";
    for(int i = 2; i < 12; ++i) {
        std::string num = std::to_string(i - 1);
        field[i] = num + std::string(26 - num.size(), ' ');
        field[i][3] = field[i].back() = '|';
    }
    field.back() = "   |_____________________|";

    const vector<Cell>& shots = player.field.getShots();
    for (const Cell& cl: shots)
        field[cl.row + 1][3 + 2 * cl.column] = '*';
    const vector<Ship>& ships = player.field.getShips();
    for (const Ship& ship: ships) {
        for (const Deck &dck: ship.getDecks()) {
            field[dck.row + 1][3 + 2 * dck.column] = dck.isShot ? 'x' : defaultForDeck;
        }
    }
    for(int i = 0; i < 13; ++i)
        std::cout << field[i] << '\n';
}

void ConsoleIO::draw(const Player& current, const Player& other) const {
    std::cout  << current.getName() << ", ваше поле: \n";
    std::cout << blue;
    drawField(current, 'S');
    std::cout << "\n\n\n";
    std::cout << reset << "Поле противника: \n";
    std::cout << red;
    drawField(other);
    std::cout << reset;
}

void ConsoleIO::registration(Player& player, int num) const {
    std::string name, pas;
    std::cout << "Игрок №" << num <<", введите своё имя: ";
    std::cin >> name;
    std::cout << name << ", придумайте пароль (пустая строка, если пароль не нужен): ";
    std::cin.ignore ( std::numeric_limits<std::streamsize>::max(), '\n' );
    std::getline(std::cin, pas);
    player = Player(name, pas);
    std::cout << clear;
}

void ConsoleIO::initializePlayers(Player& player1, Player& player2) const  {
    registration(player1, 1);
    registration(player2, 2);
    std::cout << clear;
}

void ConsoleIO::logIn(const Player& player) const {
    std::cout << player.getName() << ", ваша очередь!\n";
    std::string current = "";
    while(!player.checkPassword(current)) {
        std::cout << "Пожалуйста, введите свой пароль: ";
        std::cin >> current;
    }
}
std::string ConsoleIO::nameOfShip(int cntDecks) const {
    switch (cntDecks) {
        case 1: return "однопалубного";
        case 2: return "двухпалубного";
        case 3: return "трехпалубного";
        default: return "четырехпалубного";
    }
}

void ConsoleIO::readPlacement(int& row, int& column, char& direction, bool withDirection) const {
    while (true) {
        char c;
        std::cin >> c >> row;
        if (withDirection)
            std::cin >> direction;
        else
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        column = c - 'A' + 1;

        if(row < 1 || row > 10 || column < 1 || column > 10
           || (withDirection && direction != 'V' && direction != 'H')) {
            std::cout << "Попробуйте еще раз: ";
        } else {
            break;
        }
    }
}

void ConsoleIO::arrangeShips(Player& player) const {
    logIn(player);
    std::cout << "Позиция для однопалубного корабля вводится в формате: A1 - позиция.\n";
    std::cout << "Для расстановки многопалубных кораблей введите позицию в формате: A1 V (или H вместо V),\n";
    std::cout << "где A1 - позиция первой клетки, при этом программа будет пытаться поставить корабль 'вниз'\n";
    std::cout << "от этой клетки в случае H, и 'вправо' в случае V.\n";
    for (int cntDecks = 4; cntDecks >= 1; --cntDecks) {
        for (int i = 1; i <= 5 - cntDecks; ++i) {
            std::cout << "\nТекущее расположение ваших кораблей: \n";
            std::cout << blue;
            drawField(player, 'S');
            std::cout << reset;

            std::cout << "Введите расположение для " << i << "-ого " << nameOfShip(cntDecks) << " корабля: ";
            int row = -1;
            int column = -1;
            char direction = ' ';
            readPlacement(row, column, direction, cntDecks > 1);
            while(!player.field.tryToPlace(row, column, direction == 'V', cntDecks)) {
                std::cout << "Не удалось распложить данный корабль, попробуйте другую позицию: ";
                readPlacement(row, column, direction, cntDecks > 1);
            }
            std::cout << clear;
        }
    }
}

Cell ConsoleIO::askAttackPosition(const Player& current, const Player& other) const {
    draw(current, other);
    std::cout << "Введите клетку для атаки: ";
    char c = ' ';
    int row = -1;
    int column = -1;
    while (true) {
        std::cin >> c >> row;
        column = c - 'A' + 1;
        if (row >= 1 && row <= 10 && column >= 1 && column <= 10)
            break;
        std::cout << "Ввод некорректен, попробуйте ещё раз: ";
    }
    std::cout << clear;
    return Cell(row, column);
}

bool ConsoleIO::suggestNewGame() const {
    std::cout << "Хотите сыграть ещё одну игру? (Yes/No)\n";
    std::string answer;
    std::cin >> answer;
    while (answer != "Yes" && answer != "No") {
        std::cout << "Попробуйте ещё раз: ";
        std::cin >> answer;
    }
    return answer == "Yes";
}

void ConsoleIO::destroyMessage() const {
    std::cout << clear;
    std::cout << "Потопил(а)!\n";
}

void ConsoleIO::hitMessage() const {
    std::cout << clear;
    std::cout << "Ранил(а)!\n";
}

void ConsoleIO::missMessage() const {
    std::cout << clear;
    std::cout << "Мимо!\n";
}

void ConsoleIO::congratulate(const Player& winner) const {
    std::cout << winner.getName() << ", поздравляем с победой!\n";
}