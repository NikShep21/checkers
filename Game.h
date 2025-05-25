#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Move.h"
#include <vector>



class Game {
    Board board;
    PieceColor currentTurn;

    std::vector<Move> getAllAvailableMoves() const;

    std::vector<Move> getAvailableCapture(const Board& board , const Position& from) const;
    std::vector<Position> getAllAvailableCaptures(const Position& from) const;

public:
    Game(int width, int height, const std::string& nameFile, PieceColor startingPlayer = PieceColor::WHITE);
    Game(int width, int height, const std::vector<std::pair<Position, Piece*>>& initialPieces, PieceColor startingPlayer = PieceColor::WHITE);
    std::vector<Move> getAllMoves(const Position& from) const;
    Board& getBoard();

    

};

#endif