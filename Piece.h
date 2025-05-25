#ifndef PIECE_H
#define PIECE_H

#include "Position.h"
#include <vector>
enum class PieceColor{
    WHITE,
    BLACK

};
class Piece {
    protected:
        PieceColor color;
        Piece(PieceColor color) : color(color) {}
        
    public:
        PieceColor getColor() const { return color; }
        virtual std::vector<Position> getMoves(const Position& from, int boardWidth, int boardHeight) const = 0;
        virtual Piece* clone() const = 0;
        virtual std::vector<Position> getCaptureMoves(const Position& from, int boardWidth, int boardHeight) const = 0;
            
            
};
#endif