#ifndef KING_H
#define KING_H
#include "Piece.h"

class King: public Piece {
    public:
        King(PieceColor color);
        std::vector<Move> getMoves(const Position& from, const Board& board) const override;
        Piece* clone() const override;
        std::vector<Move> getCaptures(const Position& from, const Board& board) const override;

};


#endif