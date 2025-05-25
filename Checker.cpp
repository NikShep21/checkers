#include "Checker.h"

Checker::Checker(PieceColor color) : Piece(color){}
std::vector<Position> Checker::getMoves(const Position& from, int boardWidth, int boardHeight) const {

    std::vector<Position> moves;
    int dy = (color == PieceColor::WHITE) ? -1 : 1;

    for (int dx : {-1, 1}){
        int newX = from.x + dx;
        int newY = from.y + dy;

        if (newX >= 0 && newX < boardWidth && newY >= 0 && newY < boardHeight){
            moves.emplace_back(newX, newY);
        }
    }
    return moves;
}
Piece* Checker::clone() const {
    return new Checker(*this);
}
std::vector<Position> Checker::getCaptureMoves(const Position& from, int boardWidth, int boardHeight) const {
    std::vector<Position> captures;
    for (int dx : {-1, 1}) {
        for (int dy : {-1, 1}) {
            int newX = from.x + dx;
            int newY = from.y + dy;
            if (newX >= 0 && newX < boardWidth && newY >= 0 && newY < boardHeight) {
                captures.emplace_back(newX, newY);
            }
        }
    }
    return captures;
}