#include "Position.h"
#include <stdexcept>

Position::Position(int x, int y) : x(x), y(y) {}
//тут поменять
Position::Position(const std::string& str) {
    if (str.size() != 2 ||
        str[0] < 'A' || str[0] > 'Z' ||
        str[1] < '1' || str[1] > '9') {
        throw std::invalid_argument("Invalid position string: must be A1–Z9 or similar");
    }

    x = str[0] - 'A';
    y = str[1] - '1';
}

std::string Position::toString() const {
    char letter = 'A' + x;
    int number = y + 1;
    return std::string(1, letter) + std::to_string(number);
}

bool Position::operator==(const Position& other) const {
    return x == other.x && y == other.y;
}

std::ostream& operator<<(std::ostream& os, const Position& pos) {
    return os << pos.toString();
}
