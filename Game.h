#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Move.h"
#include <vector>



class Game {
    Board board;
    PieceColor currentTurn;

    
    // Получаем все возможные взятия для одной фигуры(проходим через рекурсию)
    std::vector<Move> getCaptureMoves(const Board& b,const Position& from, const Move& currentMove) const;
    //получаем обычные ходы у всех фигур
    std::vector<Move> getAllSimpleMoves() const;

    //получаем все возможные взятия для всех фигур
    std::vector<Move> getAllCaptureMoves() const;
    
    public:
    //конструкторы. Один запись через файл, второй через вектор позиций и фигур
    Game(int width, int height, const std::string& nameFile, PieceColor startingPlayer = PieceColor::WHITE);
    Game(int width, int height, const std::vector<std::pair<Position, Piece*>>& initialPieces, PieceColor startingPlayer = PieceColor::WHITE);
    // Получаем все возможные ходы(или взятия) для текущего игрока
    std::vector<Move> getAllMoves() const;

    //получаем доску
    const Board& getBoard() const;
    Board& getBoard();

    // проверука на возможность превращения шашки в дамку
    bool shouldPromote(const Piece* piece, const Position& pos) const;

    // метод для хода
    void makeMove(const Move& move);

    // смена текущего игрока
    void switchTurn();

    // проверка на окончание игры
    bool isGameOver() const;

    // Получаем текущего игрока
    PieceColor getCurrentTurn() const;
};

#endif