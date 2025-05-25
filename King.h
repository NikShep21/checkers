#ifndef KING_H
#define KING_H
#include "Piece.h"

class King: public Piece {
    public:
        King(PieceColor color);
        std::vector<Position> getMoves(const Position& from, int boardWidth, int boardHeight) const override;
        Piece* clone() const override;
        std::vector<Position> getCaptureMoves(const Position& from, int boardWidth, int boardHeight) const override;
};

#endif
