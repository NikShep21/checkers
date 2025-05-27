#ifndef PIECE_H
#define PIECE_H

#include "Position.h"
#include <vector>
#include "Move.h"

enum class PieceColor{
    WHITE,
    BLACK

};
class Board;
// родительский класс для шашки и дамки
class Piece {
    protected:
        PieceColor color;
        Piece(PieceColor color) : color(color) {}
        
    public:
        PieceColor getColor() const { return color; }
        virtual Piece* clone() const = 0;
        // метод для получения возможных ходов
        virtual std::vector<Move> getMoves(const Position& from, const Board& board) const = 0;
        // метод для получения возможных взятий(не множественных)
        virtual std::vector<Move> getCaptures(const Position& from, const Board& board) const = 0;

            
            
};
#endif