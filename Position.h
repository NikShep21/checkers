#ifndef POSITION_H
#define POSITION_H

#include <string>
#include <stdexcept>
#include <iostream>

struct Position {
    int x, y;

    Position(int x, int y);
    Position(const std::string& str);

    std::string toString() const;
    bool operator==(const Position& other) const;
};


std::ostream& operator<<(std::ostream& os, const Position& pos);

#endif