#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <optional>
#include "Piece.h"
#include "Position.h"
#include "Checker.h"
#include "King.h"
class Board {
    int width;
    int height;
    
    //храним доску в виде двумерного вектора указателей на фигуры
    std::vector<std::vector<Piece*>> board;

    public: 
      
        
       
        // методы для управления фигурой
        void setPiece(const Position& pos, Piece* piece); 
        void removePiece(const Position& pos);
        void transformFigure(const Position& pos); 

        // конструкторы и деструктор
        Board(int width, int height);                        
        Board(int width, int height, const std::vector<std::pair<Position, Piece*>>& initialPieces); 
        Board(const Board& other);  
        Board& operator=(const Board& other);                         
        ~Board();

        // методы для получения информации о доске
        int getWidth() const;
        int getHeight() const;
        void print() const;

        //получаем фигуру
        Piece* getPiece(Position pos);
        const Piece* getPiece(Position pos) const;
        
        bool isValid(const Position& pos) const;
        //делаем перемещение фигуры(без логики шашек, просто перемещение)
        void move(const Position& from, const Position& to);

    };

#endif
