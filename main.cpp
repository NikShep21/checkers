#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Game.h"


int main() {
   Game game(8,8, "pos.txt", PieceColor::WHITE);
   game.getBoard().print();
    return 0;
}