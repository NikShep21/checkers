#ifndef CHECKER_H
#define CHECKER_H
#include "Piece.h"
#include "Board.h"
class Checker: public Piece {
    public:
        Checker(PieceColor color);
        std::vector<Move> getMoves(const Position& from, const Board& board) const override;
        Piece* clone() const override;
        std::vector<Move> getCaptures(const Position& from, const Board& board) const override;
};

#endif
