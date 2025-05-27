#include "Game.h"
#include <iostream>
#include <vector>
#include <string>

int main(int argc, char* argv[]) {
    std::string filename;
    if (argc > 1) {
        filename = argv[1];
    } else {
        std::cout << "Enter input file name: ";
        std::cin >> filename;
    }
    // задаем размер доски
    int width = 8, height = 8;
    std::cout << "Enter board width: ";
    std::cin >> width;
    std::cout << "Enter board height: ";
    std::cin >> height;
    // задаем первый ход
    int playerChoice = 1;
    std::cout << "Who moves first?\n1. White\n2. Black\nEnter 1 or 2: ";
    std::cin >> playerChoice;
    PieceColor firstPlayer = (playerChoice == 2) ? PieceColor::BLACK : PieceColor::WHITE;

    Game game(width, height, filename, firstPlayer);
    // Запускаем игру
    while (!game.isGameOver()) {
        game.getBoard().print();
        std::cout << (game.getCurrentTurn() == PieceColor::WHITE ? "White" : "Black") << " to move\n";

        std::vector<Move> moves = game.getAllMoves();
        if (moves.empty()) break;
        // Выводим возможные ходы
        for (int i = 0; i < moves.size(); ++i) {
            std::cout << i + 1 << ": ";
            const std::vector<Position>& path = moves[i].getPath();
            for (int j = 0; j < path.size(); ++j) {
                std::cout << path[j].toString();
                if (j + 1 < path.size())
                    std::cout << (moves[i].getTaken().empty() ? '-' : 'x');
            }
            std::cout << "\n";
        }
        // Выбор хода игроком
        int choice = -1;
        while (true) {
            std::cout << "Enter move number (1-" << moves.size() << "): ";
            std::cin >> choice;
            if (choice >= 1 && choice <= static_cast<int>(moves.size())) break;
            std::cout << "Invalid move. Try again.\n";
        }

        game.makeMove(moves[choice - 1]);
    }
    // Игра окончена, выводим результат
    game.getBoard().print();
    std::cout << "Game over! ";
    if (game.getCurrentTurn() == PieceColor::WHITE)
        std::cout << "Black wins!\n";
    else
        std::cout << "White wins!\n";
    return 0;
}