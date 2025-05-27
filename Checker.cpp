#include "Checker.h"
#include "Board.h"
Checker::Checker(PieceColor color) : Piece(color){}

Piece* Checker::clone() const {
    return new Checker(*this);
}

std::vector<Move> Checker::getMoves(const Position& from, const Board& board) const{
    std::vector<Move> moves;
    int direction = (color == PieceColor::WHITE) ? 1 : -1;
    for (int dx : {-1, 1}){
        int newX = from.x + dx;
        int newY = from.y + direction;
        Position to(newX, newY);

        if(board.isValid(to) && board.getPiece(to) == nullptr){
            Move move;
            move.path = {from, to};
            moves.push_back(move);
        }

    }
    return moves;
}
std::vector<Move> Checker::getCaptures(const Position& from, const Board& board) const {
    std::vector<Move> captures;
    //проходим по всем диагоналям на одну клетку, проверяем клетку за шашкой
    for (int dx : {-1, 1}){
        for (int dy: {-1, 1}){
            int midX = from.x + dx;
            int midY = from.y + dy;
            int toX = from.x + 2 * dx;
            int toY = from.y + 2 * dy;
            Position mid(midX, midY);
            Position to(toX, toY);
            if(!board.isValid(to)) continue;
            const Piece* midPiece = board.getPiece(mid);
            if(midPiece && midPiece->getColor() != color && board.getPiece(to)==nullptr){
                 captures.emplace_back(
                    std::vector<Position>{from, to},
                    std::vector<Position>{mid}
                );
            }
        }   
    }
    return captures;
}
