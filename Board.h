#ifndef BOARD_H
#define BOARD_H
#include "vector"
#include "Piece.h"
#include "position.h"
#include <optional>
class Board{
    std::array<std::array<std::optional<Piece>, 8>, 8> cells;
    public:
    Board(const Board& other);
    const std::optional<Piece>& at(int row, int col) const;
    

    

};

#endif

//принцип по которому строим дерево позиций
//как проверяем, что именно этот ход приводят к победе