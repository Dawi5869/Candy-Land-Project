#include "Board.h"
#include <iostream>

using namespace std;

int main()
{
    Board board;
    board.movePlayer(3);
    board.movePlayer(3);
    board.displayBoard();
    
    return 0;
}