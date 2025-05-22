#include "Candystore.h"
#include "Board.h"
#include <iostream>

using namespace std;


// struct Candy
// {
//     string name;
//     string description;
//     double price;
//     string candy_type;
// };


int main()
{
    Board board;
    int count = 0;
    CandyStore candy_stores[5];

    Candy red{"red", "blah blah blah", 0.0, "boost"};
    Candy blue{"blue", "blah blah blah", 0.0, "boost"};
    Candy green{"green", "blah blah blah", 0.0, "boost"};
    Candy yellow{"yellow", "blah blah blah", 0.0, "boost"};

    candy_stores[0].addCandy(red);
    candy_stores[0].addCandy(blue);
    candy_stores[0].addCandy(green);
    candy_stores[0].addCandy(yellow);

    board.addCandyStore(42);

    for(int i = 0; i < board.getBoardSize(); i++)
    {
        board.setPlayerPosition(i);

        if (board.isPositionCandyStore(i))
        {
            board.displayBoard();

            candy_stores[count].displayCandies();
            count ++;
        }
    }
}