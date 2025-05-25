#include "King.h"

King::King(PieceColor color): Piece(color) {}
std::vector<Position> King::getMoves(const Position& from, int boardWidth, int boardHeight) const {
    std::vector<Position> moves;

    for (int dx:{-1, 1}){
        for (int dy:{-1, 1}){
            int x = from.x + dx;
            int y = from.y + dy;

            while(x >= 0 && x < boardWidth && y >= 0 && y < boardHeight){
                moves.emplace_back(x, y);
                x += dx;
                y += dy;
            }

        }
    }
    return moves;
}
std::vector<Position> King::getCaptureMoves(const Position& from, int boardWidth, int boardHeight) const {
    return getMoves(from, boardWidth, boardHeight);
}
Piece* King::clone() const {
    return new King(*this);
}