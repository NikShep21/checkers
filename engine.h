#ifndef ENGINE_H
#define ENGINE_H

#include "Game.h"
#include <string>
#include <vector>
#include <optional>

class Engine {
public:
    // Загрузка позиции из текстового файла
    static Game loadPositionFromFile(const std::string& filepath, int boardWidth = 8, int boardHeight = 8);

    // Основной метод поиска выигрышной стратегии
    std::optional<std::vector<Move>> findWinningSequence(const Game& startGame, int maxDepth = 3);

    // Сохранение найденного пути в файл
    static void saveMoveSequenceToFile(const std::vector<Move>& moves, const std::string& filepath);
};

#endif
