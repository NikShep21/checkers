#ifndef MOVE_H
#define MOVE_H

#include "Position.h"
#include <vector>

//один ход: путь фигуры и список побитых фигур
struct Move {
    std::vector<Position> path;   // путь: начальная и все последующие позиции
    std::vector<Position> taken;  // побитые фигуры (позиции)

    Move() = default;

    // Конструктор для простого хода без взятий
    Move(const std::vector<Position>& path)
        : path(path) {}

    // Конструктор для взятий
    Move(const std::vector<Position>& path, const std::vector<Position>& taken)
        : path(path), taken(taken) {}

    const std::vector<Position>& getPath() const { return path; }
    const std::vector<Position>& getTaken() const { return taken; }

   
    // Начальная и конечная позиции
    Position from() const { return path.front(); }
    Position to() const { return path.back(); }
};

#endif