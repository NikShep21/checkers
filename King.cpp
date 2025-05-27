#include "King.h"
#include "Board.h"
King::King(PieceColor color): Piece(color) {}

Piece* King::clone() const {
    return new King(*this);
}

std::vector<Move> King::getMoves(const Position& from, const Board& board) const {
    std::vector<Move> moves;
    int width = board.getWidth();
    int height = board.getHeight();

    for (int dx : {-1, 1}) {
        for (int dy : {-1, 1}) {
            int x = from.x + dx;
            int y = from.y + dy;
            while (x >= 0 && x < width && y >= 0 && y < height) {
                Position to(x, y);
                if (board.getPiece(to) == nullptr) {
                    Move move;
                    move.path = {from, to};
                    moves.push_back(move);
                } else {
                    break; 
                }
                x += dx;
                y += dy;
            }
        }
    }
    return moves;
}


std::vector<Move> King::getCaptures(const Position& from, const Board& board) const {
    std::vector<Move> captures;
    int width = board.getWidth();
    int height = board.getHeight();
    // проходим по всем диагоналям
    for (int dx : {-1, 1}) {
        for (int dy : {-1, 1}) {
            int x = from.x + dx;
            int y = from.y + dy;
            bool foundEnemy = false;
            Position enemyPos;
            while (x >= 0 && x < width && y >= 0 && y < height){
                Position pos(x, y);
                const Piece* piece = board.getPiece(pos);
                //идем пока не найдем врага или не выйдем за пределы доски
                if (!foundEnemy) {
                    if(piece == nullptr){
                        x += dx;
                        y += dy;
                        continue;
                    } 
                    else if(piece->getColor() != color){
                        foundEnemy = true;
                        enemyPos = pos;
                        x += dx;
                        y += dy;
                        continue;
                    }
                    else{
                        break;
                    }
                }
                else{
                    //записываем все ходы после врага
                    if(piece == nullptr){
                        captures.emplace_back(
                            std::vector<Position>{from, pos},
                            std::vector<Position>{enemyPos}
                        );

                        x += dx;
                        y += dy;
                    }
                    else{
                        break;
                    }
                }
            }

        }
    }
    return captures;

}