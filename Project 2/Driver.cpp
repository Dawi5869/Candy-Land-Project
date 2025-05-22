#include <iostream>
#include "Game.h"
#include "Board.h"
#include "Player.h"
#include "DeckOfCards.h"
#include "CandyStore.h"
#include <vector>

using namespace std;

int calcMovesForward(string player_name, Game &game, Card card)
{
    
    // doubles
    if(((((game.getPlayerPosition(player_name) % 3) == 0) && (card.color == "magenta")) || ((((game.getPlayerPosition(player_name)-1) % 3) == 0) && (card.color == "green")) || ((((game.getPlayerPosition(player_name)-2) % 3) == 0) && (card.color == "blue"))) && card.x2 == true)
    {
        return 6;
    }
    else if(((((game.getPlayerPosition(player_name) % 3) == 0) && (card.color == "blue")) || ((((game.getPlayerPosition(player_name)-1) % 3) == 0) && (card.color == "magenta")) || ((((game.getPlayerPosition(player_name)-2) % 3) == 0) && (card.color == "green"))) && card.x2 == true)
    {
        return 4;
    }
    else if(((((game.getPlayerPosition(player_name) % 3) == 0) && (card.color == "green")) || ((((game.getPlayerPosition(player_name)-1) % 3) == 0) && (card.color == "blue")) || ((((game.getPlayerPosition(player_name)-2) % 3) == 0) && (card.color == "magenta"))) && card.x2 == true)
    {
        return 2;
    }

    //singles
    if(((((game.getPlayerPosition(player_name) % 3) == 0) && (card.color == "magenta")) || ((((game.getPlayerPosition(player_name)-1) % 3) == 0) && (card.color == "green")) || ((((game.getPlayerPosition(player_name)-2) % 3) == 0) && (card.color == "blue"))) && card.x2 == false)
    {
        return 3;
    }
    else if(((((game.getPlayerPosition(player_name) % 3) == 0) && (card.color == "blue")) || ((((game.getPlayerPosition(player_name)-1) % 3) == 0) && (card.color == "magenta")) || ((((game.getPlayerPosition(player_name)-2) % 3) == 0) && (card.color == "green"))) && card.x2 == false)
    {
        return 2;
    }
    else if(((((game.getPlayerPosition(player_name) % 3) == 0) && (card.color == "green")) || ((((game.getPlayerPosition(player_name)-1) % 3) == 0) && (card.color == "blue")) || ((((game.getPlayerPosition(player_name)-2) % 3) == 0) && (card.color == "magenta"))) && card.x2 == false)
    {
        return 1;
    }

    return -1;
    
}

int main()
{
    // string description = "test";
    // Candy test11{"Jellybean Vigor", description, "stamina", 50 ,0.0, "Treasure"};
    // Candy test21{"Jellybean Vigor", description, "stamina", 50 ,0.0, "Treasure"};
    // Candy candy_array1[3] = {test11, test21, test21};
    // Player player1 = Player(5, 100, "Start of game", candy_array1, 3);
    // player1.setName("Player1");

    // Candy test12{"Jellybean Vigor", description, "stamina", 50 ,0.0, "Treasure"};
    // Candy test22{"Jellybean Vigor", description, "stamina", 50 ,0.0, "Treasure"};
    // Candy candy_array2[3] = {test12, test22, test22};
    // Candy empty[4] = {{}};
    // Player player2 = Player(5, 100, "No candy!", empty, 4);
    // player2.setName("Player2");

    // Candy test{"Jellybean Vigor", description, "stamina", 50 ,0.0, "Treasure"};
    // Candy test2{"Jellybean Vigor", description, "stamina", 50 ,0.0, "Treasure"};
    // Candy candy_array[3] = {test, test2, test2};
    // Player player = Player(5, 100, "Start of game", candy_array, 3);
    // player.setName("Player");

    Game game;
    // game.addPlayer(player1);
    // game.addPlayer(player2);
    // game.addPlayer(player);

    // game.printPlayers();
    // cout << "-------------" << endl;


    // game.removePlayer(player2.getName());

    // vector<Player> players = game.getPlayers();

    // cout << "Players: " << endl;
    // for (int i = 0; i < int(players.size()); i++)
    // {
    //     cout << players.at(i).getName() << endl;
    // }

    // cout << "-------------" << endl;

    // game.printPlayers();

    Board board;
    // board.movePlayer(2, game, player2.getName());
    // board.movePlayer(5, game, player1.getName()); 
    // board.movePlayer(2, game, player2.getName());
    // board.movePlayer(6, game, player.getName());
    // board.movePlayer(-4, game, player.getName());


    DeckOfCards deck;
    deck.setCards();

    board.setTiles(game);

    game.setCandies();
    // cout << "------------" << endl;

    // game.printCandies();
    // cout << "------------" << endl;

    game.setCharacters();

    // game.displayCharacters();

    game.gameStart();

    

    board.showTileTypes();
    cout << endl;
    cout << endl;
    cout << "===============================================" << endl;
    cout << "Lets Begin! Here is the playing board." << endl;
    cout << "===============================================" << endl;
    cout << endl;
    cout << endl;
    
    board.displayBoard(game);


    vector<Player> players = game.getPlayers();


    while (game.checkWinner() == false)
    {
        for (int i = 0; i < game.getNumOfPlayers(); i++)
        {
            string player_name = players.at(i).getName();
            cout << "It is " << player_name << "'s turn" << endl;
            cout << "Please select menu option: " << endl;
            cout << "1.    Draw a card" << endl;
            cout << "2.    Use candy" << endl;
            cout << "3.    Show player stats" << endl;
            int choice1;
            cin >> choice1;

            if(choice1 == 1)
            {
                cout << "To draw a card press D" << endl;
                char draw;
                cin >> draw;

                Card card = deck.drawCard();
                if (card.x2)
                {
                    cout << "You drew a double " << card.color << " card." << "here is the updated trail:" << endl;
                    game.setPlayerPosition(player_name, game.getPlayerPosition(player_name) + calcMovesForward(player_name, game, card));
                    Tile tile = board.getTile(game.getPlayerPosition(player_name));
                    board.playTile(tile.tile_type, player_name, game);
                }
                else
                {
                    cout << "You drew a " << card.color << " card." << "here is the updated trail:" << endl;
                    game.setPlayerPosition(player_name, game.getPlayerPosition(player_name) + calcMovesForward(player_name, game, card));
                    Tile tile = board.getTile(game.getPlayerPosition(player_name));
                    board.playTile(tile.tile_type, player_name, game);
                }

                board.displayBoard(game);
            }
            else if(choice1 == 2)
            {
                cout << "what candy would you like to use" << endl;
                players.at(i).printInventory();

                string candy_name;
                cin >> candy_name;


                board.useCandy(player_name, candy_name, game);
            }
            else if (choice1 == 3)
            {
                game.printPlayerStats(player_name);
            }
        }
    }
    

    return 0;
}