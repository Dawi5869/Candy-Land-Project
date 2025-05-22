#include "Board.h"
#include "Game.h"
// #include "Player.h"
// #include "DeckOfCards.h"
#include <cstdlib>
#include <ctime>

#include <vector>


using namespace std;

int calcRandom2(int smaller, int larger)
{
    srand(time(0));
    
    int diff = (larger+1) - smaller;
    if (diff == 0)
    {
        cout << "Error: diff = 0" << endl;
        return -1;
    }
    int random = (rand() % diff) + smaller;
    return random;
}

bool rockPaperScissors1()
{
    int CPU = calcRandom2(0, 2);
    // string choices[] = {"rock", "paper", "scissors"};

    int player;
    cout << "Enter 1 to play Rock, Enter 2 to play paper, or Enter 3 to play scissors!" << endl;
    cin >> player;

    while (player <= 0 && player >=4)
    {
        cout << "Please enter a number between 1 and 3." << endl;
        cin >> player;
    }

    player -= 1;

    while (player == CPU)
    {
        cout << "Tie! Try again!" << endl;

        CPU = calcRandom2(0, 2);
        // string choices[] = {"rock", "paper", "scissors"};

        cout << "Enter 1 to play Rock, Enter 2 to play paper, or Enter 3 to play scissors!" << endl;
        cin >> player;

        while (player <= 0 && player >=4)
        {
            cout << "Please enter a number between 1 and 3." << endl;
            cin >> player;
        }

        player -= 1;
    }

    if ((CPU == 0 && player == 1) || (CPU == 1 && player == 2) || (CPU == 2 && player == 0))
    {
        cout << "You won! You have successfully escaped!" << endl;
        return true;
    }
    else
    {
        cout << "OH NO! Looks like you lost! You were unable to escape." << endl;
        return false;
    }

}

//------------------------------------------------------------------------------------------------------------------------------------

Board::Board()
{
    resetBoard();
}

void Board::resetBoard()
{
    const int COLOR_COUNT = 3;
    const string COLORS[COLOR_COUNT] = {MAGENTA, GREEN, BLUE};
    Tile new_tile;
    string current_color;

    


    for (int i = 0; i < _BOARD_SIZE - 1; i++)
    {
        current_color = COLORS[i % COLOR_COUNT];
        new_tile = {current_color, "regular"};
        _tiles[i] = new_tile;
    }
    new_tile = {ORANGE, "regular"};
    _tiles[_BOARD_SIZE - 1] = new_tile;

    _candy_store_count = 0;
    for (int i = 0; i < _MAX_CANDY_STORE; i++)
    {
        _candy_store_position[i] = -1;
    }

    _player_position = 0;


}

void Board::displayTile(int position, Game game1)
{
    if (position < 0 || position >= _BOARD_SIZE)
    {
        return;
    }
    Tile target = _tiles[position];
    cout << target.color << " ";
    
    if(_tiles[position].tile_type == "lost turn" || _tiles[position].tile_type == "lost 2 turns")
    {
        cout << "G";
    }

    bool store = false;
    for (int i = 0; i < _MAX_CANDY_STORE; i++)
    {
        
        
        if (position == game1.getStorPosition(i)) 
        {
            cout << "C" ;
            store = true;
        }
        
    }

    vector<Player> players = game1.getPlayers();
    bool player = false;
    for (int i = 0; i < game1.getNumOfPlayers(); i++)
    {
        
    
        
        if (position == players[i].getPosition() && int(players[i].getTilesMoved().size()) != 0)
        {
            cout << i+1;
            player = true;
        }
        
    }

    

    if (player == false && store == false)
    {
        cout << " ";
    }
    cout << " " << RESET;
}

void Board::displayBoard(Game game)
{
    // First horizontal segment
    for (int i = 0; i <= 23; i++)
    {
        displayTile(i, game);
    }
    cout << endl;
    // First vertical segment
    for (int i = 24; i <= 28; i++)
    {
        for (int j = 0; j < 23; j++)
        {
            cout << "   ";
        }
        displayTile(i, game);
        cout << endl;
    }
    // Second horizontal segment
    for (int i = 52; i > 28; i--)
    {
        displayTile(i, game);
    }
    cout << endl;
    // Second vertical segment
    for (int i = 53; i <= 57; i++)
    {
        displayTile(i, game);
        for (int j = 0; j < 23; j++)
        {
            cout << "   ";
        }
        cout << endl;
    }
    // Third horizontal segment
    for (int i = 58; i < _BOARD_SIZE; i++)
    {
        displayTile(i, game);
    }
    cout << ORANGE << "Castle" << RESET << endl;
}

bool Board::setPlayerPosition(int new_position)
{
    if (new_position >= 0 && new_position < _BOARD_SIZE)
    {
        _player_position = new_position;
        return true;
    }
    return false;
}

int Board::getBoardSize() const
{
    return _BOARD_SIZE;
}

int Board::getCandyStoreCount() const
{
    return _candy_store_count;
}

int Board::getPlayerPosition() const
{
    return _player_position;
}

bool Board::addCandyStore(int position)
{
    if (_candy_store_count >= _MAX_CANDY_STORE)
    {
        return false;
    }
    _candy_store_position[_candy_store_count] = position;
    _candy_store_count++;
    return true;
}

bool Board::isPositionCandyStore(int board_position)
{
    for (int i = 0; i < _candy_store_count; i++)
    {
        if(_candy_store_position[i] == board_position)
        {
            return true;
        }
    }
    return false;
}

bool Board::movePlayer(int tile_to_move_forward, Game &game, string name)
{

    int new_player_position = tile_to_move_forward + game.getPlayerPosition(name);
    if(new_player_position < 0 || new_player_position >= _BOARD_SIZE)
    {
        return false;
    }
    game.setPlayerPosition(name, new_player_position);
    game.setPlayerStamina(name, game.getPlayerStamina(name) - 1);
    return true;
}

void Board::setTiles(Game &game)
{


    //setting candy stores
    game.setCandyStoreNumbers();
    vector<int> magentaTiles;
    for (int i = 0; i <= 27; i++)
    {
        if (i % 3 == 0 && i!= 0)
        {
            magentaTiles.push_back(i);
        }
    }


    vector<int> greenTiles;
    for (int i = 28; i <= 54; i++)
    {
        if ((i-1) % 3== 0)
        {
            greenTiles.push_back(i);
        }
    }

    vector<int> blueTiles;
    for (int i = 55; i <= 82; i++)
    {
        if ((i-2) % 3== 0)
        {
            blueTiles.push_back(i);
        }
    }

    // cout << magentaTiles.size() << endl;
    // cout << greenTiles.size() << endl;
    // cout << blueTiles.size() << endl;


    int store1 = calcRandom2(0, int(magentaTiles.size())-1);
    store1 = magentaTiles.at(store1);
    game.setStorePosition(1, store1);
    _tiles[store1].tile_type = "candyStore";
    // _candy_store_position[0] = store1;
    addCandyStore(store1);

    int store2 = calcRandom2(0, int(greenTiles.size())-1);
    store2 = greenTiles.at(store2);
    game.setStorePosition(2, store2);
    _tiles[store2].tile_type = "candyStore";
    // _candy_store_position[1] = store2;
    addCandyStore(store2);

    int store3 = calcRandom2(0, int(blueTiles.size())-1);
    store3 = blueTiles.at(store3);
    game.setStorePosition(3, store3);
    _tiles[store3].tile_type = "candyStore";
    // _candy_store_position[2] = store3;
    addCandyStore(store3);

    // _candy_store_count = 3;

    // setting other tile types
    // string tile_types[] = {"regular", "shortcut", "icecreamShop", "gumdropForest", "gingerbreadHouse", "candyStore", "hiddenTreasures"};


    for (int i = 0; i < _BOARD_SIZE - 1; i++)
    {
        
        //------------------------------calculting random number seeded with loop iteration ---------------------------------------------------
        int larger = 71;
        int smaller = 0;
        srand(time(0)+i);
    
        int diff = (larger+1) - smaller;
        if (diff == 0)
        {
            cout << "Error: diff = 0" << endl;
        }
        int random = (rand() % diff) + smaller;

        int num = random;

        //---------------------------------------------------------------------------------------------------------------------------------


        if(isPositionCandyStore(i) == false)
        {
            if (num <= 46)
            {
                // _tiles[i].tile_type = "regular";

                int larger1 = 100;
                int smaller1 = 0;
                srand(time(0)+i);
            
                int diff1 = (larger1+1) - smaller1;
                if (diff1 == 0)
                {
                    cout << "Error: diff = 0" << endl;
                }
                int random1 = (rand() % diff1) + smaller1;

                int num1 = random1;

                if(num1 <= 40)
                {
                    _tiles[i].tile_type = "calamity";
                }
                else
                {
                    _tiles[i].tile_type = "regular";
                }

            }
            else if (num <= 51)
            {
                _tiles[i].tile_type = "shortcut";
            }
            else if (num <= 56)
            {
                _tiles[i].tile_type = "icecreamShop";
            }
            else if (num <= 61)
            {
                _tiles[i].tile_type = "gumdropForest";
            }
            else if (num <= 66)
            {
                _tiles[i].tile_type = "gingerbreadHouse";
            }
            else if (num <= 71)
            {
                _tiles[i].tile_type = "hiddenTreasures";
            }
        }
    }
}


void Board::showTileTypes()
{
    for (int i = 0; i < _BOARD_SIZE-1; i++)
    {
        cout << "Tile" << i+1 << " " << _tiles[i].tile_type;
        if (_tiles[i].tile_type == "candyStore")
        {
            cout << "------------ candyStore here";
        }
        
        cout << endl;
    }
}


void Board::setTileType(string tile_type, int index)
{
    _tiles[index].tile_type = tile_type;
}



void Board::useCandy(string player_name, string candy_name, Game &game)
{
    Candy candy = game.findPlayerCandy(player_name, candy_name);

    if(candy.name == "")
    {
        cout << "Candy named: " << candy_name << " not found." << endl;
        return;
    }

    if (candy.candy_type == "magical")
    {
        if(candy.effect == "stamina")
        {
            game.setPlayerStamina(player_name, game.getPlayerStamina(player_name) + candy.effect_value);

            if (game.getPlayerStamina(player_name) > 100)
            {
                game.setPlayerStamina(player_name, 100);
            }
            cout << "By using the " << candy_name << "candy your Stamina has been increased by " << candy.effect_value << "." << endl;
            game.printPlayerStats(player_name);
            game.removePlayerCandy(player_name, candy_name);
        }
        else if(candy.effect == "gold")
        {
            game.setPlayerGold(player_name, game.getPlayerGold(player_name) + candy.effect_value);
            
            if (game.getPlayerGold(player_name) > 100)
            {
                game.setPlayerGold(player_name, 100);
            }

            cout << "By using the " << candy_name << "candy your gold has been increased by " << candy.effect_value << "coins." << endl;
            game.printPlayerStats(player_name);
            game.removePlayerCandy(player_name, candy_name);
        }
        else if(candy.effect == "other")
        {
            cout << "Can't use this candy here. This candy is only used for defense." << endl;
        }
    }
    else if (candy.candy_type == "poison")
    {
        if(candy.effect == "stamina")
        {
            cout << "Please enter the name of the player you wish to gift this candy to:" << endl;
            string player_choice;
            cin >> player_choice;
            game.setPlayerStamina(player_choice, game.getPlayerStamina(player_choice) + candy.effect_value);
            
            if (game.getPlayerStamina(player_choice) > 100)
            {
                game.setPlayerStamina(player_choice, 100);
            }
            cout << "By using the " << candy_name << "candy your Stamina has been increased by " << candy.effect_value << "." << endl;
            game.printPlayerStats(player_choice);
            game.removePlayerCandy(player_choice, candy_name);
        }
        else if(candy.effect == "gold")
        {
            cout << "Please enter the name of the player you wish to gift this candy to:" << endl;
            string player_choice;
            cin >> player_choice;
            
            game.setPlayerGold(player_choice, game.getPlayerGold(player_choice) + candy.effect_value);
            
            if (game.getPlayerGold(player_choice) > 100)
            {
                game.setPlayerGold(player_choice, 100);
            }

            cout << "By using the " << candy_name << "candy your gold has been increased by " << candy.effect_value << "coins." << endl;
            game.printPlayerStats(player_choice);
            game.removePlayerCandy(player_choice, candy_name);
        }
        
    }
    else if (candy.candy_type == "gummy")
    {
        cout << "What tile (that is not a candy store) would you like to use this candy on: " << endl;
        int tile_num;
        cin >> tile_num;

        if(abs(candy.effect_value) == 2)
        {
            setTileType("lost 2 turns", tile_num-1);
        }
        else if(abs(candy.effect_value) == 1)
        {
            setTileType("lost turn", tile_num-1);
            
        }
        
        
        game.setPlayerTurnsLost(player_name, game.getPlayerTurnsLost(player_name) + candy.effect_value);
        cout << "The " << candy_name << " candy has now been placed on tile number " << tile_num << " and is displayed as G for gummy tile." << endl;
        cout << "Anyone who steps on this tile will lose " << abs(candy.effect_value) << " turn(s)." << endl;
        game.removePlayerCandy(player_name, candy_name);
    }
}

void Board::playTile(string tile_type, string player_name, Game &game)
{
    // int index = game.playerIndexByName(player_name);

    // cout << "playTile function" << endl;
    if (tile_type == "shortcut")
    {
        game.setPlayerPosition(player_name, game.getPlayerPosition(player_name) + 4);
        cout << "you have come across a shortcut! You character has mooved ahead by 4 tiles" << endl;
    }


    else if (tile_type == "iceCreamShop")
    {
        cout << "You have come across an ice cream stop! you get to draw another card" << endl; // ------- incomplete
    }


    else if (tile_type == "gumdropForest")
    {
        int num = calcRandom2(5, 10);
        game.setPlayerGold(player_name, game.getPlayerGold(player_name) - num);
        game.setPlayerPosition(player_name, game.getPlayerPosition(player_name) - 4);
        cout << "You have come across a gumdrop forest! Your position was set back 4 tiles and you lost " << num << " gold coins." << endl;
    }


    else if (tile_type == "gingerbreadHouse")
    {
        game.setPlayerPosition(player_name, game.getPlayerTilesMoved(player_name).at(int(game.getPlayerTilesMoved(player_name).size()) - 1));
    }
    


    else if (tile_type == "hiddenTreasures")
    {
        int num = calcRandom2(1, 100);

        if(num <= 30)
        {
            // stamina refill
            int added_stamina = calcRandom2(10, 30);
            game.setPlayerStamina(player_name, game.getPlayerPosition(player_name) + added_stamina);
            if (game.getPlayerPosition(player_name) > 100)
            {
                game.setPlayerStamina(player_name, 100);
            }

            cout << "Hidden treasure! You stamina increased by " << added_stamina << "." << endl;
        }
        else if (num <= 40)
        {
            // gold windfall
            int gold_amount = calcRandom2(20, 40);
            game.setPlayerGold(player_name, game.getPlayerGold(player_name) + gold_amount);
            if (game.getPlayerGold(player_name) > 100)
            {
                game.setPlayerGold(player_name, 100);
            }

            cout << "Hidden treasure! You gold increased by " << gold_amount << " coins." << endl;
        }
        else if (num <= 70)
        {
            // robbers repel
            vector<Candy> inventory = game.getPlayerInventory(player_name);
            Candy robbers_repel = {"Robers Repel", "Prevents opponents from stealing gold if they land on the same tile", "other", 0, 0.0, "imunity"};
            if (inventory.at(int(inventory.size())-1).name != "")
            {
                cout << "Would you like to swap one of your candies for the Robbers Repel candy?. Enter 1 for yes or 2 for no: " << endl;
                int choice; 
                cin >> choice;
                if(choice == 1)
                {
                    cout << "Enter name of candy you wish to swap out: " << endl;
                    string candy_name;
                    cin >> candy_name; 
                    
                    game.SwapCandy(player_name, robbers_repel, candy_name);
                    cout << "The Robbers Repel candy has been added to your inventory in place of the "<< candy_name <<"candy!" << endl;
                }
                else
                {
                    cout << "The Robbers Repel candy has been left behind" << endl;
                }
            }
            else
            {
                game.addPlayerCandy(player_name, robbers_repel); 
                cout << "The Robbers Repel candy has been added to your inventory!" << endl;
            }
        }
        else 
        {
            // candy acquisition
            int candy_num = calcRandom2(1, 100);

            if(candy_num <= 70)
            {
                // jellybean vigor
                string description = "Using the Jellybean of Vigor, you can restore 50 units of stamina.";

                Candy jellybean_vigor = {"Jellybean Vigor", description, "stamina", 50 ,0.0, "magical"};
                vector<Candy> inventory = game.getPlayerInventory(player_name);
                if (inventory.at(int(inventory.size())-1).name != "")
                {
                    cout << "Would you like to swap one of your candies for the Jellybean Vigor candy?. Enter 1 for yes or 2 for no: " << endl;
                    int choice; 
                    cin >> choice;
                    if(choice == 1)
                    {
                        cout << "Enter name of candy you wish to swap out: " << endl;
                        string candy_name;
                        cin >> candy_name; 
                        
                        game.SwapCandy(player_name, jellybean_vigor, candy_name);
                        cout << "The Jellybean Vigor candy has been added to your inventory in place of the "<< candy_name <<"candy!" << endl;
                    }
                    else
                    {
                        cout << "The Jellybean Vigor candy has been left behind" << endl;
                    }
                }

            }
            else
            {
                // Treasure Hunter's Truffle
                string description = " This candy allows the player to unlock a hidden treasure by solving a riddle";
                Candy treasure_hunters_truffle = {"Treasure Hunter's Truffle", description, "other", 0,  0.0, "magical"};
                vector<Candy> inventory = game.getPlayerInventory(player_name);
                if (inventory.at(int(inventory.size())-1).name != "")
                {
                    cout << "Would you like to swap one of your candies for the Treasure Hunter's Truffle candy?. Enter 1 for yes or 2 for no: " << endl;
                    int choice; 
                    cin >> choice;
                    if(choice == 1)
                    {
                        cout << "Enter name of candy you wish to swap out: " << endl;
                        string candy_name;
                        cin >> candy_name; 
                        
                        game.SwapCandy(player_name, treasure_hunters_truffle, candy_name);
                        cout << "The Treasure Hunter's Truffle candy has been added to your inventory in place of the "<< candy_name <<"candy!" << endl;
                    }
                    else
                    {
                        cout << "The Treasure Hunter's Truffle candy has been left behind" << endl;
                    }
                }

            }
        }
    }


    else if (tile_type == "calamity")
    {
        int num = calcRandom2(1, 100);

        if (num <= 30)
        {
            // candy bandits
            int gold_amount = calcRandom2(1, 10);
            game.setPlayerGold(player_name, game.getPlayerGold(player_name) - gold_amount);
            if (game.getPlayerGold(player_name) < 0)
            {
                game.setPlayerGold(player_name, 0);
            }

            cout << "Oh no! Candy Bandits have swiped your gold coins!" << endl;

        }
        else if (num <= 65)
        {
            // lollipop labyrinth

            cout << "Oh dear! You got lost in the lollipop labyrinth!" << endl;
            bool winner = rockPaperScissors1();

            if(winner == false)
            {
                
                game.setPlayerEffect(player_name, "lost turn");
                cout << "You are now lost in the grand Lollipop Labyrinth." 
                    " It will take you some time to find your way out. Your next turn is skipped" << endl;
            }
            


        }
        else if (num <= 80)
        {
            // candy avalanche
            cout << "Watch out! A candy avalanche has struck!" << endl;
            bool winner = rockPaperScissors1();
            
            if(winner == false)
            {
                int lost_stamina = calcRandom2(5, 10);
                game.setPlayerStamina(player_name, game.getPlayerStamina(player_name) - lost_stamina);
                if (game.getPlayerStamina(player_name) < 0)
                {
                    game.setPlayerStamina(player_name, 0);
                }
                game.setPlayerEffect(player_name, "lost turn");

                cout << "You were struck by the candy avalanche! It will take you some time to recover."
                    "Your stamina has decreased by " << lost_stamina << " and your next turn will be skipped" << endl;
            }



        }
        else 
        {
            // sticky taffy trap

            cout << "Oops! You are stuck in a sticky taffy trap!" << endl;

            
            vector<Candy> inventory = game.getPlayerInventory(player_name);
            vector<Candy> magic_candies = game.candyByEffect(inventory, 0 , "magical");

            if(int(magic_candies.size()) > 0)
            {
                cout << "One of your magical cards was used to escape." << endl;
                game.removePlayerCandy(player_name, magic_candies.at(0).name);
            }

            else
            {
                game.setPlayerEffect(player_name, "lost turn");
                cout << "You are now stuck in a taffy trap. Your next turn will be skipped" << endl;
            }
            

        }
    }


    else if (tile_type == "candyStore")
    {
        cout << "You landed on a tile which has a candy store." << endl;
        cout << endl;
        cout << "Do you want to visit the candy story? (y/n)" << endl;
        char choice;
        cin >> choice;

        if (choice == 'y')
        {
            
        }
        else
        {

        }
        
        //---------------------------------------------------------------------------------------------------------------- incomplete
    }



    else if (tile_type == "lost turn")
    {
        game.setPlayerTurnsLost(player_name, game.getPlayerTurnsLost(player_name)-1);
    }
    else if (tile_type == "lost 2 turns")
    {
        game.setPlayerTurnsLost(player_name, game.getPlayerTurnsLost(player_name)-2);
    }
}


Tile Board::getTile(int position)
{
    return _tiles[position];
}