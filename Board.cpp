#include "Board.h"
#include <iostream>

// Конструктор по размеру
Board::Board(int width, int height)
    : width(width), height(height), board(height, std::vector<Piece*>(width, nullptr)) {}

// Конструктор с начальными фигурами
Board::Board(int width, int height, const std::vector<std::pair<Position, Piece*>>& initialPieces)
    : Board(width, height) {
    for (const auto& [pos, piece] : initialPieces) {
        if (isValid(pos)) {
            board[pos.y][pos.x] = piece;
        }
    }
}

// Копирующий конструктор (глубокая копия)
Board::Board(const Board& other)
    : width(other.width), height(other.height), board(height, std::vector<Piece*>(width, nullptr)) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (other.board[y][x]) {
                board[y][x] = other.board[y][x]->clone(); // глубокая копия фигуры
            }
        }
    }
}

// Оператор присваивания (глубокая копия)
Board& Board::operator=(const Board& other) {
    if (this == &other) return *this;

    // Удалим старые фигуры
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            delete board[y][x];
        }
    }

    width = other.width;
    height = other.height;
    board.resize(height, std::vector<Piece*>(width, nullptr));

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (other.board[y][x]) {
                board[y][x] = other.board[y][x]->clone();
            } else {
                board[y][x] = nullptr;
            }
        }
    }

    return *this;
}

// Деструктор
Board::~Board() {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            delete board[y][x];
        }
    }
}

// Вспомогательные методы
void Board::setPiece(const Position& pos, Piece* piece) {
    if (isValid(pos)) {
        delete board[pos.y][pos.x]; // удаляем старую фигуру, если есть
        board[pos.y][pos.x] = piece;
    }
}
void Board::removePiece(const Position& pos) {
    if (isValid(pos)) {
        delete board[pos.y][pos.x];
        board[pos.y][pos.x] = nullptr;
    }
}

// Здесь можно реализовать превращение шашки в дамку
void Board::promotePiece(const Position& pos) {
    if (!isValid(pos) || !board[pos.y][pos.x]) return;

    Piece* original = board[pos.y][pos.x];
    if (dynamic_cast<Checker*>(original)) {
        PieceColor color = original->getColor();
        delete original;
        board[pos.y][pos.x] = new King(color);
    }
}

// Геттеры
int Board::getWidth() const {
    return width;
}

int Board::getHeight() const {
    return height;
}

Piece* Board::getPiece(Position pos){
    if (pos.x < 0 || pos.y < 0 || pos.y >= height || pos.x >= width) return nullptr;
    return board[pos.y][pos.x];
}

const Piece* Board::getPiece(Position pos) const {
    if (pos.x < 0 || pos.y < 0 || pos.y >= height || pos.x >= width) return nullptr;
    return board[pos.y][pos.x];
}

bool Board::isValid(const Position& pos) const {
    return pos.x >= 0 && pos.x < width && pos.y >= 0 && pos.y < height;
}

// Печать доски 
void Board::print() const {
    // Верхняя рамка с буквами
    std::cout << "  ";
    for (int x = 0; x < width; ++x) {
        std::cout << static_cast<char>('A' + x) << ' ';
    }
    std::cout << '\n';

    // Основная доска (снизу вверх)
    for (int y = height - 1; y >= 0; --y) {
        std::cout << y + 1 << ' ';
        for (int x = 0; x < width; ++x) {
            if (board[y][x] == nullptr) {
                std::cout << ". ";
            } else if (dynamic_cast<const Checker*>(board[y][x])) {
                std::cout << (board[y][x]->getColor() == PieceColor::WHITE ? "w " : "b ");
            } else {
                std::cout << (board[y][x]->getColor() == PieceColor::WHITE ? "W " : "B ");
            }
        }
        std::cout << '\n';
    }
}
