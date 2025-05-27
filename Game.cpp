#include "Game.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>

const Board& Game::getBoard() const{
    return board;
}

Board& Game::getBoard(){
    return board;
}


Game::Game(int width, int height, const std::string& nameFile, PieceColor startingPlayer)
    : board(width, height), currentTurn(startingPlayer){

    std::ifstream file(nameFile);
    if(!file.is_open()){
        throw std::runtime_error("Could not open file: " + nameFile);
    }
    std::string line;
    PieceColor color = PieceColor::WHITE;
    while (std::getline(file, line)){
        if(line.empty()) continue;
        if(line.find("White:") == 0){
            color = PieceColor::WHITE;
            continue;
        } else if(line.find("Black:") == 0){
            color = PieceColor::BLACK;
            continue;
        }
        try {
            if(line[0] == 'M'){
                Position pos(line.substr(1));
                board.setPiece(pos, new King(color));
            }else{
                Position pos(line);
                board.setPiece(pos, new Checker(color));
            }
        }
        catch(const std::invalid_argument& e) {
            throw std::runtime_error("Invalid position in file: " + line + " - " + e.what());
        }
    }
}


Game::Game(int width, int height, const std::vector<std::pair<Position, Piece*>>& initialPieces, PieceColor startingPlayer )
    : board(width, height), currentTurn(startingPlayer) {
    
    for (std::vector<std::pair<Position, Piece*>>::const_iterator it = initialPieces.begin(); it != initialPieces.end(); ++it) {
        const Position& pos = it->first;
        const Piece* piece = it->second;
        if (!board.isValid(pos)) {
            throw std::invalid_argument("Invalid position: " + pos.toString());
        }
        board.setPiece(pos, piece->clone());
    }
}


std::vector<Move> Game::getAllSimpleMoves() const {
    std::vector<Move> moves;
    for (int y = 0; y < board.getHeight(); ++y) {
        for (int x = 0; x < board.getWidth(); ++x) {
            Position from(x, y);
            const Piece* piece = board.getPiece(from);
            if (!piece || piece->getColor() != currentTurn) continue;
            std::vector<Move> pieceMoves = piece->getMoves(from, board);
            moves.insert(moves.end(), pieceMoves.begin(), pieceMoves.end());
        }
    }
    return moves;
}

std::vector<Move> Game::getCaptureMoves(const Board& b, const Position& from, const Move& currentMove) const {
    std::vector<Move> results;

    const Piece* piece = b.getPiece(from);
    if (!piece || piece->getColor() != currentTurn) return results;

    std::vector<Move> possibleCaptures = piece->getCaptures(from, b);
    if (possibleCaptures.empty()) return results;

    for (std::vector<Move>::const_iterator moveIt = possibleCaptures.begin(); moveIt != possibleCaptures.end(); ++moveIt) {
        const Move& move = *moveIt;
        // Проверка: не бьем уже побитую фигуру
        bool alreadyTaken = false;
        for (std::vector<Position>::const_iterator takenPosIt = move.getTaken().begin(); takenPosIt != move.getTaken().end(); ++takenPosIt) {
            if (std::find(currentMove.getTaken().begin(), currentMove.getTaken().end(), *takenPosIt) != currentMove.getTaken().end()) {
                alreadyTaken = true;
                break;
            }
        }
        if (alreadyTaken) continue;

        Board newBoard = b;
        Position newPos = move.to();

        
        newBoard.move(from, newPos);
        if (shouldPromote(piece, newPos)) {
            newBoard.transformFigure(newPos);
        }

        std::vector<Position> fullPath = currentMove.getPath();
        if (fullPath.empty()) fullPath.push_back(from); // начальная точка
        fullPath.insert(fullPath.end(), move.getPath().begin() + 1, move.getPath().end());

        std::vector<Position> fullTaken = currentMove.getTaken();
        fullTaken.insert(fullTaken.end(), move.getTaken().begin(), move.getTaken().end());

        Move extendedMove(fullPath, fullTaken);

        // Рекурсивный вызов
        std::vector<Move> nextCaptures = getCaptureMoves(newBoard, newPos, extendedMove);
        if (nextCaptures.empty()) {
            results.push_back(extendedMove); // цепочка завершена
        } else {
            results.insert(results.end(), nextCaptures.begin(), nextCaptures.end());
        }
    }

    return results;
}

std::vector<Move> Game::getAllCaptureMoves() const {
    std::vector<Move> allCaptures;

    for (int y = 0; y < board.getHeight(); ++y) {
        for (int x = 0; x < board.getWidth(); ++x) {
            Position from(x, y);
            const Piece* piece = board.getPiece(from);
            if (!piece || piece->getColor() != currentTurn) continue;

            std::vector<Move> captures = getCaptureMoves(board, from, Move());
            allCaptures.insert(allCaptures.end(), captures.begin(), captures.end());
        }
    }

    return allCaptures;
}

bool Game::shouldPromote(const Piece* piece, const Position& pos) const {
    if (!piece) return false;
    if (dynamic_cast<const King*>(piece)) return false;

    int height = board.getHeight();

    // Белая шашка достигает верхнего ряда (для неё это нижняя строка по Y)
    if (piece->getColor() == PieceColor::WHITE && pos.y == height - 1) return true;

    // Чёрная шашка достигает нижнего ряда (верхняя строка по Y)
    if (piece->getColor() == PieceColor::BLACK && pos.y == 0) return true;

    return false;
}

std::vector<Move> Game::getAllMoves() const {
    std::vector<Move> captures = getAllCaptureMoves();
    if (!captures.empty()) return captures;
    return getAllSimpleMoves();
}

void Game::makeMove(const Move& move) {
    if (move.getPath().size() < 2) return;

    // Удаляем все побитые фигуры
    for (std::vector<Position>::const_iterator takenIt = move.getTaken().begin(); takenIt != move.getTaken().end(); ++takenIt) {
        board.removePiece(*takenIt);
    }

    // Двигаем фигуру по всей цепочке
    std::vector<Position> path = move.getPath();
    Position from = path.front();

    for (size_t i = 1; i < path.size(); ++i) {
        Position to = path[i];
        board.move(from, to);

        Piece* piece = board.getPiece(to);
        // Проверяем превращение на каждом шаге
        if (shouldPromote(piece, to)) {
            board.transformFigure(to);
        }
        from = to;
    }

    switchTurn();
}

bool Game::isGameOver() const {
    // Проверяем, есть ли ходы у белых
    Game whiteGame = *this;
    whiteGame.currentTurn = PieceColor::WHITE;
    if (!whiteGame.getAllMoves().empty()) return false;

    // Проверяем, есть ли ходы у чёрных
    Game blackGame = *this;
    blackGame.currentTurn = PieceColor::BLACK;
    if (!blackGame.getAllMoves().empty()) return false;

    // Нет ходов ни у одной стороны — партия окончена
    return true;
}

void Game::switchTurn() {
    currentTurn = (currentTurn == PieceColor::WHITE) ? PieceColor::BLACK : PieceColor::WHITE;
}

PieceColor Game::getCurrentTurn() const {
    return currentTurn;
}