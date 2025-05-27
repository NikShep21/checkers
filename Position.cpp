#include "Position.h"
#include <stdexcept>

Position::Position() : x(0), y(0) {}
Position::Position(int x, int y) : x(x), y(y) {}

Position::Position(const std::string& str) {
    if (str.size() < 2 || str.size() > 3 ||
        str[0] < 'A' || str[0] > 'Z') {
        throw std::invalid_argument("Invalid position string: must be A1–Z99 or similar");
    }

    x = str[0] - 'A';
    try {
        y = std::stoi(str.substr(1)) - 1;
    } catch (...) {
        throw std::invalid_argument("Invalid position string: must be A1–Z99 or similar");
    }
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
