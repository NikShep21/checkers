#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <optional>
#include "Piece.h"
#include "Position.h"
#include "Checker.h"
#include "King.h"
class Board {
    public:
        int width;
        int height;
        std::vector<std::vector<Piece*>> board;
    
        void setPiece(const Position& pos, Piece* piece); 
        void removePiece(const Position& pos);
        void promotePiece(const Position& pos);


    
        Board(int width, int height);                        
        Board(int width, int height, const std::vector<std::pair<Position, Piece*>>& initialPieces); 
        Board(const Board& other);  
        Board& operator=(const Board& other);                         
        ~Board();


        int getWidth() const;
        int getHeight() const;
        void print() const;

        Piece* getPiece(Position pos);
        const Piece* getPiece(Position pos) const;
        bool isValid(const Position& pos) const;

    };

#endif
