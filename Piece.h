#ifndef PIECE_H
#define PIECE_H


enum class PieceType{
    DEFAULT,
    KING
};
enum class PieceColor{
    WHILE,
    BLACK
};

class Piece{
    PieceType type;
    PieceColor color;

    public:

    Piece(PieceColor color, PieceType type);
    PieceColor getColor() const;
    bool isKing() const;
    void promote();

};


#endif