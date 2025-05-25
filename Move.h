#ifndef MOVE_H
#define MOVE_H

#include "Position.h"
#include <vector>
#include <cmath>

// Represents a move: a sequence of positions (for multi-capture moves)
struct Move {
    std::vector<Position> path; // includes starting and subsequent landing positions

    bool isCapture() const {
        if (path.size() < 2) return false;
        // A capture moves over an opponent piece (diagonal distance > 1) or has more than one jump
        return path.size() > 2 ||
               (std::abs(path[0].x - path[1].x) > 1 && std::abs(path[0].y - path[1].y) > 1);
    }
};

#endif