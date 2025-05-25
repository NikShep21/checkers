// #include "Engine.h"
// #include <fstream>
// #include <sstream>
// #include <queue>
// #include <unordered_set>
// #include <iostream>

// // =======================
// // Загрузка позиции из файла
// // =======================
// Game Engine::loadPositionFromFile(const std::string& filepath, int boardWidth, int boardHeight) {
//     std::ifstream file(filepath);
//     if (!file.is_open()) throw std::runtime_error("Failed to open file: " + filepath);

//     std::vector<std::pair<Position, Piece>> pieces;
//     std::string line;
//     PieceColor currentColor;

//     while (std::getline(file, line)) {
//         if (line.find("White:") != std::string::npos) {
//             currentColor = PieceColor::WHITE;
//         } else if (line.find("Black:") != std::string::npos) {
//             currentColor = PieceColor::BLACK;
//         } else if (!line.empty()) {
//             Position pos(line);
//             pieces.emplace_back(pos, Piece(currentColor, PieceType::DEFAULT));
//         }
//     }

//     return Game(boardWidth, boardHeight, pieces, PieceColor::WHITE);
// }

// // =======================
// // Рекурсивный поиск гарантированной победы
// // =======================
// static bool dfs(Game& game, int depth, int maxDepth, std::vector<Move>& path, PieceColor playerTurn, bool maximizingPlayer) {
//     if (depth > maxDepth) return false;
//     if (game.isGameOver()) return game.getCurrentTurn() != playerTurn;

//     auto moves = game.getAllPossibleMoves(true);
//     if (moves.empty()) return game.isGameOver() && game.getCurrentTurn() != playerTurn;

//     if (maximizingPlayer) {
//         for (const auto& move : moves) {
//             Game next = game;
//             if (!next.makeMove(move)) continue;
//             path.push_back(move);
//             if (dfs(next, depth + 1, maxDepth, path, playerTurn, false)) {
//                 return true;
//             }
//             path.pop_back();
//         }
//         return false;
//     } else {
//         for (const auto& move : moves) {
//             Game next = game;
//             if (!next.makeMove(move)) continue;
//             if (!dfs(next, depth + 1, maxDepth, path, playerTurn, true)) {
//                 return false; // есть хотя бы один ход соперника, после которого мы не побеждаем
//             }
//         }
//         return true; // против любого ответа мы побеждаем
//     }
// }

// std::optional<std::vector<Move>> Engine::findWinningSequence(const Game& startGame, int maxDepth) {
//     std::vector<Move> path;
//     Game root = startGame;
//     if (dfs(root, 0, maxDepth, path, root.getCurrentTurn(), true)) {
//         return path;
//     }
//     return std::nullopt;
// }

// // =======================
// // Сохранение результата в файл
// // =======================
// void Engine::saveMoveSequenceToFile(const std::vector<Move>& moves, const std::string& filepath) {
//     std::ofstream file(filepath);
//     if (!file.is_open()) throw std::runtime_error("Failed to open output file: " + filepath);

//     for (const auto& move : moves) {
//         file << move.from.toString() << " -> " << move.to.toString() << "\n";
//     }

//     file.close();
// }
