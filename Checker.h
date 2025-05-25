#ifndef CHECKER_H
#define CHECKER_H
#include "Piece.h"

class Checker: public Piece {
    public:
        Checker(PieceColor color);
        std::vector<Position> getMoves(const Position& from, int boardWidth, int boardHeight) const override;
        Piece* clone() const override;
        std::vector<Position> getCaptureMoves(const Position& from, int boardWidth, int boardHeight) const override;
};

#endif
