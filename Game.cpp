#include "Game.h"
#include <fstream>
#include <sstream>
#include <stdexcept>


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
    
    for (const auto& [pos, piece] : initialPieces) {
        if (!board.isValid(pos)) {
            throw std::invalid_argument("Invalid position: " + pos.toString());
        }
        board.setPiece(pos, piece->clone());
    }
}


std::vector<Move> Game::getAllAvailableMoves() const {
    std::vector<Move> moves;
    for (int y = 0; y < board.getHeight(); ++y){
        for(int x = 0; x < board.getWidth(); ++x){
            const Piece* piece = board.getPiece(Position(x, y));
            if(!piece || piece->getColor() != currentTurn) continue;

            std::vector<Position> dest = piece->getMoves(Position(x, y), board.getWidth(), board.getHeight());
            for (const Position& pos: dest){
                if(board.getPiece(pos) == nullptr){
                    Move move;
                    move.path = {Position(x, y), pos};
                    moves.push_back(move);
                }
            }
        }

    }
}