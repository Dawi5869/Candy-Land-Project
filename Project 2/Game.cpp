#include <iostream>
#include "Player.h"
#include "CandyStore.h"
#include "Game.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;


int calcRandom3(int smaller, int larger)
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


bool rockPaperScissors()
{
    int CPU = calcRandom3(0, 2);
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

        CPU = calcRandom3(0, 2);
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


// ------------------------------------------------------------------------
// ------------------------------------------------------------------------



Game::Game()
{
    _num_of_players = 0;
    
    
    for (int i = 0; i < _MAX_NUM_PLAYERS; i++)
    {
        Player player;
        _players[i] = player;
        
    }
}




void Game::addPlayer(Player player)
{
    // string name = player.getName();
    // _players[_num_of_players].setName(name);

    // string effect = player.getEffect();
    // _players[_num_of_players].setEffect(effect);

    // int stamina = player.getStamina();
    // _players[_num_of_players].setStamina(stamina);

    // double gold = player.getGold();
    // _players[_num_of_players].setGold(gold);

    // int candy_amount = player.getCandyAmount();
    // _players[_num_of_players].setCandyAmount(candy_amount);

    // vector<Candy> inventory = player.getInventory();
    // _players[_num_of_players].emptyInventory();
    // for (int i = 0; i < int(inventory.size()); i++)
    // {
    //     _players[_num_of_players].addCandy(inventory.at(i));
    // }

    // int position = player.getPosition();
    // _players[_num_of_players].setPosition(position);

    _players[_num_of_players] = player;

    _num_of_players += 1;
}


void Game::setNumOfPlayers(int num_of_players)
{
    _num_of_players = num_of_players;
}

void Game::removePlayer(string name)
{

    for(int i = 0; i < _MAX_NUM_PLAYERS; i++)
    {
        if (_players[i].getName() == name)
        {
            for (int j = i; j < (_MAX_NUM_PLAYERS - 1); j++)
            {
                // _players[j].setName(_players[j+1].getName());
                // _players[j].setStamina(_players[j+1].getStamina());
                // _players[j].setEffect(_players[j+1].getEffect());
                // _players[j].setGold(_players[j+1].getGold());
                // _players[j].setPosition(_players[j+1].getPosition());

                // vector<Candy> inventory = _players[j+1].getInventory();
                // _players[j].emptyInventory();
                // for (int k = 0; k < int(inventory.size()); k++)
                // {
                //     _players[j].addCandy(inventory.at(k));
                // }
                _players[j] = _players[j+1];
            }
        }
    }
    Player empty_player;
    _players[_MAX_NUM_PLAYERS - 1] = empty_player;

    _num_of_players -= 1;
}

vector<Player> Game::getPlayers()
{
    vector<Player> players;
    for (int i = 0; i < _num_of_players; i++)
    {
        players.push_back(_players[i]);
    }

    return players;
}

int Game::getNumOfPlayers()
{
    return _num_of_players;
}

void Game::printPlayers()
{
    for (int i = 0; i < _MAX_NUM_PLAYERS; i++)
    {
        cout << _players[i].getName() << endl;
    }
}

int Game::playerIndexByName(string name)
{
    for (int i = 0; i < _num_of_players; i++)
    {
        if (name == _players[i].getName())
        {
            return i;
        }
    }

    return -1;
}



//------------------------------Loading the game------------------------------
//----------------------------------------------------------------------------

void Game::setCandies()
{
    ifstream candies_file;
    candies_file.open("Candies.txt");

    if (!(candies_file.is_open()))
    {
        cout << "Candies file could not open" << endl;
        return;
    }

    string line;
    while (getline(candies_file, line))
    {
        stringstream ss1(line);
        

        Candy candy;

        string name;
        string effect;
        string description;
        string effect_value;
        string price;
        string candy_type;

        getline(ss1, name, '|');
        candy.name = name;

        getline(ss1, description, '|');
        candy.description = description;

        getline(ss1, effect, '|');
        candy.effect = effect;


        getline(ss1, effect_value, '|');
        candy.effect_value = stoi(effect_value);

        getline(ss1, candy_type, '|');
        candy.candy_type = candy_type;

        getline(ss1, price);
        candy.price = stod(price);

        _candies.push_back(candy);

    }

    candies_file.close();


}

// struct Candy
// {
//     string name;
//     string description;
//     string effect;
//     int effect_value;
//     double price;
//     string candy_type;
// };


Candy Game::candyByName(string candy_name)
{

    for (int i = 0; i < int(_candies.size()); i++)
    {
        if (_candies.at(i).name == candy_name)
        {
            return _candies.at(i);
        }
    }
    cout << "Candy named " << candy_name << " not found." << endl;
    Candy candy;
    return candy;
}


void Game::setCharacters()
{

// ---------------------------------------------------
// ---------------------------------------------------

    ifstream characters_file;
    characters_file.open("Characters.txt");

    if (!(characters_file.is_open()))
    {
        cout << "Charcters file could not open" << endl;
        return;
    }

    string line;
    // vector<Character> characters;
    
    while(getline(characters_file, line))
    {
        stringstream ss1(line);
        

        Character character;

        string name;
        string stamina;
        string gold;
        string candies;

        getline(ss1, name, '|');
        character.name = name;


        getline(ss1, stamina, '|');
        character.stamina = stoi(stamina);

        getline(ss1, gold, '|');
        character.gold = stod(gold);

        getline(ss1, candies);
        candies = candies.substr(0, candies.length() - 1);
        stringstream ss2(candies);
        
        string candy;
        while (getline(ss2, candy, ',')) 
        {
            // cout << "-" << candy << "-" << endl;
            Candy candy2 = candyByName(candy);
            character.candies.push_back(candy2);
        }

        // int last_cut = 0;
        // for (int i = 0; i < int(candies.length()); i++)
        // {
        //     if (candies[i] == '|')
        //     {
        //         cout << candies.substr(last_cut,i) << endl;
        //         character.candies.push_back(candies.substr(last_cut,i));
        //         last_cut = i + 1;
        //     }
        // }

        _characters.push_back(character);
    }

// ---------------------------------------------------
// ---------------------------------------------------

//     for (int i = 0; i < 8; i++)
//     {
//         Character character;
//         character.name = "Test Character";
//         character.stamina = 100;
//         character.gold = 20;
        
//         vector<Candy> candies;
//         for (int j = 0; j < 4; j++)
//         {
//             candies.push_back(_candies.at(j));
//         }

//         character.candies = candies;

//         _characters.push_back(character);
//     }
// }


// struct Character
// {
//     string name;
//     int stamina;
//     double gold;
//     vector<Candy> candies;
};


void Game::printCandies()
{

    for(int i = 0; i < int(_candies.size()); i++)
    {
        cout << _candies.at(i).name << endl;
    }
}


void Game::fillCandyStores()
{
    for(int i = 0; i < 3; i++)
    {
        
        for (int j = 0; j < 3; j++)
        {
            srand(time(0) + j);
            int larger = int(_candies.size()) - 1;
            int smaller = 0;
            int diff = (larger+1) - smaller;
            if (diff == 0)
            {
                cout << "Error: diff = 0" << endl;
                return;
            }
            int random = (rand() % diff) + smaller;
            

            Candy candy = _candies.at(random);
            
            _stores[i].addCandy(candy);
        }
    }
}














//------------------------------Functions for Player class------------------------------
//--------------------------------------------------------------------------------------

void Game::setPlayerName(string player_name, string Name)
{
    int index = playerIndexByName(player_name);

    if (index != -1)
    {
        _players[index].setName(Name);
    }
    else
    {
        cout << "Player not found" << endl;
    }
}


void Game::setPlayerEffect(string player_name, string Effect)
{
    int index = playerIndexByName(player_name);

    if (index != -1)
    {
        _players[index].setEffect(Effect);
    }
    else
    {
        cout << "Player not found" << endl;
    }
}


void Game::setPlayerStamina(string player_name, int Stamina)
{
    int index = playerIndexByName(player_name);

    if (index != -1)
    {
        _players[index].setStamina(Stamina);
    }
    else
    {
        cout << "Player not found" << endl;
    }
}


void Game::setPlayerNumber(string player_name, int Number)
{
    int index = playerIndexByName(player_name);

    if (index != -1)
    {
        _players[index].setNumber(Number);
    }
    else
    {
        cout << "Player not found" << endl;
    }
}


void Game::setPlayerPosition(string player_name, int Position)
{
    int index = playerIndexByName(player_name);

    if (index != -1)
    {
        addPlayerTileMoved(player_name, (Position - _players[index].getPosition()));
        _players[index].setPosition(Position);

    }
    else
    {
        cout << "Player not found" << endl;
    }
}


void Game::setPlayerCandyAmount(string player_name, int CandyAmount)
{
    int index = playerIndexByName(player_name);

    if (index != -1)
    {
        _players[index].setCandyAmount(CandyAmount);
    }
    else
    {
        cout << "Player not found" << endl;
    }
}


void Game::setPlayerGold(string player_name, double Gold)
{
    int index = playerIndexByName(player_name);

    if (index != -1)
    {
        _players[index].setGold(Gold);
    }
    else
    {
        cout << "Player not found" << endl;
    }
}


int Game::getPlayerPosition(string player_name)
{
    int index = playerIndexByName(player_name);

    if (index != -1)
    {
        return _players[index].getPosition();
    }
    else
    {
        cout << "Player not found" << endl;
        return -1;
    }
}


int Game::getPlayerStamina(string player_name)
{
    int index = playerIndexByName(player_name);

    if (index != -1)
    {
        return _players[index].getStamina();
    }
    else
    {
        cout << "Player not found" << endl;
        return -1;
    }
}


double Game::getPlayerGold(string player_name)
{
    int index = playerIndexByName(player_name);

    if (index != -1)
    {
        return _players[index].getStamina();
    }
    else
    {
        cout << "Player not found" << endl;
        return -1.0;
    }
}


string Game::getPlayerEffect(string player_name)
{
    int index = playerIndexByName(player_name);

    if (index != -1)
    {
        return _players[index].getEffect();
    }
    else
    {
        cout << "Player not found" << endl;
        return "";
    }
}


void Game::printPlayerInventory(string player_name)
{
    int index = playerIndexByName(player_name);

    _players[index].printInventory();
}


Candy Game::findPlayerCandy(string player_name, string candy_name)
{
    int index = playerIndexByName(player_name);

    return _players[index].findCandy(candy_name);
}


bool Game::addPlayerCandy(string player_name, Candy candy)
{
    int index = playerIndexByName(player_name);

    return _players[index].addCandy(candy);
}


bool Game::removePlayerCandy(string player_name, string candy_name)
{
    int index = playerIndexByName(player_name);

    return _players[index].removeCandy(candy_name);
}


vector<Candy> Game::getPlayerInventory(string player_name)
{
    int index = playerIndexByName(player_name);

    return _players[index].getInventory();
}


int Game::getPlayerNumber(string player_name)
{
    int index = playerIndexByName(player_name);

    if (index != -1)
    {
        return _players[index].getNumber();
    }
    else
    {
        cout << "Player not found" << endl;
        return -1;
    }
}


void Game::emptyPlayerInventory(string player_name)
{
    int index = playerIndexByName(player_name);

    _players[index].emptyInventory();
}


int Game::getPlayerCandyAmount(string player_name)
{
    int index = playerIndexByName(player_name);

    if (index != -1)
    {
        return _players[index].getCandyAmount();
    }
    else
    {
        cout << "Player not found" << endl;
        return -1;
    }
}



vector<int> Game::getPlayerTilesMoved(string player_name)
{
    int index = playerIndexByName(player_name);

    if (index != -1)
    {
        return _players[index].getTilesMoved();
    }
    else
    {
        cout << "Player not found" << endl;
        vector<int> vec;
        return vec;
    }
}


void Game::setPlayerTilesMoved(string player_name, vector<int> tiles_moved)
{
    int index = playerIndexByName(player_name);

    if (index != -1)
    {
        _players[index].setTilesMoved(tiles_moved);
    }
    else
    {
        cout << "Player not found" << endl;
    }
}


void Game::addPlayerTileMoved(string player_name, int num)
{
    int index = playerIndexByName(player_name);

    _players[index].addTileMoved(num);
}


void Game::emptyPlayerTilesMoved(string player_name)
{
    int index = playerIndexByName(player_name);

    _players[index].emptyTilesMoved();
}


string Game::getPlayerCharacter(string player_name)
{
    int index = playerIndexByName(player_name);

    if (index != -1)
    {
        return _players[index].getCharacter();
    }
    else
    {
        cout << "Player not found" << endl;
        string str1 = "";
        return str1;
    }
}


void Game::setPlayerCharacter(string player_name, string character)
{
    int index = playerIndexByName(player_name);

    if (index != -1)
    {
        _players[index].setCharacter(character);
    }
    else
    {
        cout << "Player not found" << endl;
    }
}


void Game::setPlayerTurnsLost(string player_name, int num)
{
    int index = playerIndexByName(player_name);

    if (index != -1)
    {
        _players[index].setTurnsLost(num);
    }
    else
    {
        cout << "Player not found" << endl;
    }
}


int Game::getPlayerTurnsLost(string player_name)
{
    int index = playerIndexByName(player_name);

    if (index != -1)
    {
        return _players[index].getTurnsLost();
    }
    else
    {
        cout << "Player not found" << endl;
        int num = 0;
        return num;
    }
}

vector<Candy> Game::candyByEffect(vector<Candy> inventory, int effect_value, string candy_type)
{
    vector<Candy> candies_of_effect;
    for(int i = 0; i < int(inventory.size()); i++)
    {
        if(inventory.at(i).candy_type == candy_type && inventory.at(i).effect_value >= effect_value)
        {
            candies_of_effect.push_back(inventory.at(i));
        }
    }
    return candies_of_effect;
}

void Game::SwapCandy(string player_name, Candy candy2add, string candy2remove)
{
    int index = playerIndexByName(player_name);

    _players[index].swapCandy(candy2add, candy2remove);
}












//------------------------------Functions for CandyStore class------------------------------
//------------------------------------------------------------------------------------------


void Game::setCandyStoreNumbers()
{

    for (int i = 0; i < _MAX_NUM_STORES; i++)
    {
        CandyStore temp = CandyStore(i+1);
        _stores[i] = temp;
    }
}

void Game::setStorePosition(int store_number, int position)
{
    _stores[store_number-1].setPosition(position);
}


int Game::getStorPosition(int store_number)
{
    return _stores[store_number].getPosition();
}


void Game::displayStoreCandies(int store_number, Player &player)
{
    _stores[store_number - 1].displayCandies(player);
}


bool Game::addStoreCandy(int store_number, Candy candy)
{
    return _stores[store_number].addCandy(candy);
}


bool Game::removeStoreCandy(int store_number, string candy_name)
{
    return _stores[store_number].removeCandy(candy_name);
}




//------------------------------Tile operations------------------------------
//---------------------------------------------------------------------------

// struct Candy
// {
//     string name;
//     string description;
//     double price;
//     string candy_type;
// };

// void Game::playTile(string tile_type, string player_name)
// {
//     int index = playerIndexByName(player_name);

//     if (tile_type == "shortcut")
//     {
//         _players[index].setPosition(_players[index].getPosition() + 4);
//     }


//     else if (tile_type == "iceCreamShop")
//     {
//         // draw card again ------------------------------------------------------------ incomplete
//     }


//     else if (tile_type == "gumdropForest")
//     {
//         int num = calcRandom3(5, 10);
//         _players[index].setGold(_players[index].getGold() - num);
//         _players[index].setPosition(_players[index].getPosition() - 4);
//     }


//     else if (tile_type == "gingerbreadHouse")
//     {
//         setPlayerPosition(_players[index].getName(), _players[index].getTilesMoved().at(int(_players[index].getTilesMoved().size()) - 1));
//     }


//     else if (tile_type == "hiddenTreasures")
//     {
//         int num = calcRandom3(1, 100);

//         if(num <= 30)
//         {
//             // stamina refill
//             int added_stamina = calcRandom3(10, 30);
//             _players[index].setStamina(_players[index].getStamina() + added_stamina);
//             if (_players[index].getStamina() > 100)
//             {
//                 _players[index].setStamina(100);
//             }
//         }
//         else if (num <= 40)
//         {
//             // gold windfall
//             int gold_amount = calcRandom3(20, 40);
//             _players[index].setGold(_players[index].getGold() + gold_amount);
//             if (_players[index].getGold() > 100)
//             {
//                 _players[index].setGold(100);
//             }
//         }
//         else if (num <= 70)
//         {
//             // robbers repel
//             vector<Candy> inventory = getPlayerInventory(player_name);
//             Candy robbers_repel = {"Robers Repel", "Prevents opponents from stealing gold if they land on the same tile", "other", 0, 0.0, "imunity"};
//             if (inventory.at(int(inventory.size())-1).name != "")
//             {
//                 cout << "Would you like to swap one of your candies for the Robbers Repel candy?. Enter 1 for yes or 2 for no: " << endl;
//                 int choice; 
//                 cin >> choice;
//                 if(choice == 1)
//                 {
//                     cout << "Enter name of candy you wish to swap out: " << endl;
//                     string candy_name;
//                     cin >> candy_name; 
                    
//                     SwapCandy(player_name, robbers_repel, candy_name);
//                     cout << "The Robbers Repel candy has been added to your inventory in place of the "<< candy_name <<"candy!" << endl;
//                 }
//                 else
//                 {
//                     cout << "The Robbers Repel candy has been left behind" << endl;
//                 }
//             }
//             else
//             {
//                 addPlayerCandy(player_name, robbers_repel); 
//                 cout << "The Robbers Repel candy has been added to your inventory!" << endl;
//             }
//         }
//         else 
//         {
//             // candy acquisition
//             int candy_num = calcRandom3(1, 100);

//             if(candy_num <= 70)
//             {
//                 // jellybean vigor
//                 string description = "Using the Jellybean of Vigor, you can restore 50 units of stamina.";

//                 Candy jellybean_vigor = {"Jellybean Vigor", description, "stamina", 50 ,0.0, "magical"};
//                 vector<Candy> inventory = getPlayerInventory(player_name);
//                 if (inventory.at(int(inventory.size())-1).name != "")
//                 {
//                     cout << "Would you like to swap one of your candies for the Jellybean Vigor candy?. Enter 1 for yes or 2 for no: " << endl;
//                     int choice; 
//                     cin >> choice;
//                     if(choice == 1)
//                     {
//                         cout << "Enter name of candy you wish to swap out: " << endl;
//                         string candy_name;
//                         cin >> candy_name; 
                        
//                         SwapCandy(player_name, jellybean_vigor, candy_name);
//                         cout << "The Jellybean Vigor candy has been added to your inventory in place of the "<< candy_name <<"candy!" << endl;
//                     }
//                     else
//                     {
//                         cout << "The Jellybean Vigor candy has been left behind" << endl;
//                     }
//                 }

//             }
//             else
//             {
//                 // Treasure Hunter's Truffle
//                 string description = " This candy allows the player to unlock a hidden treasure by solving a riddle";
//                 Candy treasure_hunters_truffle = {"Treasure Hunter's Truffle", description, "other", 0,  0.0, "magical"};
//                 vector<Candy> inventory = getPlayerInventory(player_name);
//                 if (inventory.at(int(inventory.size())-1).name != "")
//                 {
//                     cout << "Would you like to swap one of your candies for the Treasure Hunter's Truffle candy?. Enter 1 for yes or 2 for no: " << endl;
//                     int choice; 
//                     cin >> choice;
//                     if(choice == 1)
//                     {
//                         cout << "Enter name of candy you wish to swap out: " << endl;
//                         string candy_name;
//                         cin >> candy_name; 
                        
//                         SwapCandy(player_name, treasure_hunters_truffle, candy_name);
//                         cout << "The Treasure Hunter's Truffle candy has been added to your inventory in place of the "<< candy_name <<"candy!" << endl;
//                     }
//                     else
//                     {
//                         cout << "The Treasure Hunter's Truffle candy has been left behind" << endl;
//                     }
//                 }

//             }
//         }
//     }


//     else if (tile_type == "calamity")
//     {
//         int num = calcRandom3(1, 100);

//         if (num <= 30)
//         {
//             // candy bandits
//             int gold_amount = calcRandom3(1, 10);
//             _players[index].setGold(_players[index].getGold() - gold_amount);
//             if (_players[index].getGold() < 0)
//             {
//                 _players[index].setGold(0);
//             }

//             cout << "Oh no! Candy Bandits have swiped your gold coins!" << endl;

//         }
//         else if (num <= 65)
//         {
//             // lollipop labyrinth

//             cout << "Oh dear! You got lost in the lollipop labyrinth!" << endl;
//             bool winner = rockPaperScissors();

//             if(winner == false)
//             {
                
//                 _players[index].setEffect("lost turn");
//                 cout << "You are now lost in the grand Lollipop Labyrinth." 
//                     " It will take you some time to find your way out. Your next turn is skipped" << endl;
//             }
            


//         }
//         else if (num <= 80)
//         {
//             // candy avalanche
//             cout << "Watch out! A candy avalanche has struck!" << endl;
//             bool winner = rockPaperScissors();
            
//             if(winner == false)
//             {
//                 int lost_stamina = calcRandom3(5, 10);
//                 _players[index].setStamina(_players[index].getStamina() - lost_stamina);
//                 if (_players[index].getStamina() < 0)
//                 {
//                     _players[index].setStamina(0);
//                 }
//                 _players[index].setEffect("lost turn");

//                 cout << "You were struck by the candy avalanche! It will take you some time to recover."
//                     "Your stamina has decreased by " << lost_stamina << " and your next turn will be skipped" << endl;
//             }



//         }
//         else 
//         {
//             // sticky taffy trap

//             cout << "Oops! You are stuck in a sticky taffy trap!" << endl;

            
//             vector<Candy> inventory = getPlayerInventory(player_name);
//             vector<Candy> magic_candies = candyByEffect(inventory, "magical", 0);

//             if(int(magic_candies.size()) > 0)
//             {
//                 cout << "One of your magical cards was used to escape." << endl;
//                 removePlayerCandy(player_name, magic_candies.at(0).name);
//             }

//             else
//             {
//                 _players[index].setEffect("lost turn");
//                 cout << "You are now stuck in a taffy trap. Your next turn will be skipped" << endl;
//             }
            

//         }
//     }


//     else if (tile_type == "candyStore")
//     {
//         cout << "You landed on a tile which has a candy store." << endl;
//         cout << endl;
//         cout << "Do you want to visit the candy story? (y/n)" << endl;
//         char choice;
//         cin >> choice;

//         if (choice == 'y')
//         {
            
//         }
//         else
//         {

//         }
        
//         //---------------------------------------------------------------------------------------------------------------- incomplete
//     }



//     else if (tile_type == "lost turn")
//     {
//         setPlayerTurnsLost(player_name, getPlayerTurnsLost(player_name)-1);
//     }
//     else if (tile_type == "lost 2 turns")
//     {
//         setPlayerTurnsLost(player_name, getPlayerTurnsLost(player_name)-2);
//     }
// }


// void Game::useCandy(string player_name, string candy_name, Board &board)
// {
//     Candy candy = findPlayerCandy(player_name, candy_name);

//     if(candy.name == "")
//     {
//         cout << "Candy named: " << candy_name << " not found." << endl;
//         return;
//     }

//     if (candy.candy_type == "magical")
//     {
//         if(candy.effect == "stamina")
//         {
//             setPlayerStamina(player_name, getPlayerStamina(player_name) + candy.effect_value);

//             if (getPlayerStamina(player_name) > 100)
//             {
//                 setPlayerStamina(player_name, 100);
//             }
//             cout << "By using the " << candy_name << "candy your Stamina has been increased by " << candy.effect_value << "." << endl;
//             printPlayerStats(player_name);
//             removePlayerCandy(player_name, candy_name);
//         }
//         else if(candy.effect == "gold")
//         {
//             setPlayerGold(player_name, getPlayerGold(player_name) + candy.effect_value);
            
//             if (getPlayerGold(player_name) > 100)
//             {
//                 setPlayerGold(player_name, 100);
//             }

//             cout << "By using the " << candy_name << "candy your gold has been increased by " << candy.effect_value << "coins." << endl;
//             printPlayerStats(player_name);
//             removePlayerCandy(player_name, candy_name);
//         }
//         else if(candy.effect == "other")
//         {
//             cout << "Can't use this candy here. This candy is only used for defense." << endl;
//         }
//     }
//     else if (candy.candy_type == "poison")
//     {
//         if(candy.effect == "stamina")
//         {
//             cout << "Please enter the name of the player you wish to gift this candy to:" << endl;
//             string player_choice;
//             cin >> player_choice;
//             setPlayerStamina(player_choice, getPlayerStamina(player_choice) + candy.effect_value);
            
//             if (getPlayerStamina(player_choice) > 100)
//             {
//                 setPlayerStamina(player_choice, 100);
//             }
//             cout << "By using the " << candy_name << "candy your Stamina has been increased by " << candy.effect_value << "." << endl;
//             printPlayerStats(player_choice);
//             removePlayerCandy(player_choice, candy_name);
//         }
//         else if(candy.effect == "gold")
//         {
//             cout << "Please enter the name of the player you wish to gift this candy to:" << endl;
//             string player_choice;
//             cin >> player_choice;
            
//             setPlayerGold(player_choice, getPlayerGold(player_choice) + candy.effect_value);
            
//             if (getPlayerGold(player_choice) > 100)
//             {
//                 setPlayerGold(player_choice, 100);
//             }

//             cout << "By using the " << candy_name << "candy your gold has been increased by " << candy.effect_value << "coins." << endl;
//             printPlayerStats(player_choice);
//             removePlayerCandy(player_choice, candy_name);
//         }
        
//     }
//     else if (candy.candy_type == "gummy")
//     {
//         cout << "What tile (that is not a candy store) would you like to use this candy on: " << endl;
//         int tile_num;
//         cin >> tile_num;

//         if(abs(candy.effect_value) == 2)
//         {
//             board.setTileType("lost 2 turns", tile_num-1)
//         }
//         else if(abs(candy.effect_value) == 1)
//         {
//             board.setTileType("lost turn", tile_num-1)
//         }
        
        
//         setPlayerTurnsLost(player_name, getPlayerTurnsLost(player_name) + candy.effect_value)
//         cout << "The " << candy_name << " candy has now been placed on tile number " << tile_num << " and is displayed as G for gummy tile." << endl;
//         cout << "Anyone who steps on this tile will lose " << abs(candy.effect_value) << " turn(s)." << endl;
//         removePlayerCandy(player_name, candy_name);
//     }
// }


void Game::printPlayerStats(string player_name)
{
    cout << "Here are your stats:" << endl;
    cout << "Player name: " << player_name << endl;
    cout << "Character: " << getPlayerCharacter(player_name) << endl;
    cout << "Stamina: " << getPlayerStamina(player_name) << endl;
    cout << "Gold: " << getPlayerGold(player_name) << endl;
    printPlayerInventory(player_name);

}


bool Game::skipTurn(string player_name)
{
    if (getPlayerTurnsLost(player_name) < 0)
    {
        setPlayerTurnsLost(player_name, getPlayerTurnsLost(player_name) + 1);
        return true;
    }
    return false;
}



//------------------------------Beginning of the game------------------------------
//---------------------------------------------------------------------------------

void Game::displayCharacters()
{
    

    int j = 0;
    string name = "";
    for (int i = 0; i < int(_characters.size()); i++)
    {

        cout << "Name: " << _characters.at(i).name << endl;
        cout << "Stamina: " << _characters.at(i).stamina << endl;
        cout << "Gold: " << _characters.at(i).gold << endl;
        
        cout << "Candies" << endl;


        for(int k = 0; k < 9; k++)
        {
            if (k < int(_characters.at(i).candies.size()))
            {
                name = _characters.at(i).candies.at(k).name;
            }
            else
            {
                name = "Empty";
            }

            cout << "|[" << name << "]";

            if(++j == 3)
            {
                cout << "|" << endl;
                
                j = 0;
            }
        }
        cout << "--------------------------------------------------------------" << endl;
        
    }
    
    
}


int Game::findCharacterIndex(string character_name)
{
    for (int i = 0; i < int(_characters.size()); i++)
    {
        if (_characters.at(i).name == character_name)
        {
            return i;
        }
    }
    return -1;
}

Character Game::characterByName(string name)
{
    for (int i = 0; i < int(_characters.size()); i++)
    {
        if (_characters.at(i).name == name)
        {
            return _characters.at(i);
        }
    }
    Character character;
    return character;
}


// void Game::removeCharacter(string character_name)
// {
//     int index = findCharacterIndex(character_name);
//     for (int i = index; i < int(_characters.size())-1; i++)
//     {
//         _characters;
//     }
// }


void Game::gameStart()
{
    cout << "Welcome to the game of candyland. Please enter the number of participants.(2-8)" << endl;
    cin >> _num_of_players;


    for (int i = 0; i < _num_of_players; i++)
    {
        cout << "Enter player name: "  << endl;
        string name;
        cin >> name;

        _players[i].setName(name);

        cout << "Awsome! Here is a list of characters a player can select from: " << endl;
        cout << endl;

        displayCharacters();

        cout << "The selected character is: " << endl;
        string character;
        cin >> character;


        _players[i].setCharacter(character);

        Character character1 = characterByName(character);

        _players[i].setStamina(character1.stamina);
        _players[i].setGold(character1.gold);
        _players[i].emptyInventory();
        
        for (int i = 0; i < int(character1.candies.size()); i++)
        {
            _players[i].addCandy(character1.candies.at(i));
        }

        cout << endl;
        cout << endl;

        cout << "==============================================================================================" << endl;
        cout << "==============================================================================================" << endl;

        _players[i].setPosition(0);

        vector<int> tiles_moved;
        _players[i].setTilesMoved(tiles_moved);

    }
}

bool Game::checkWinner()
{
    for(int i = 0; i < _num_of_players; i++)
    {
        if(_players[i].getPosition() >= 83)
        {
            cout << "=============================================" << endl;
            cout << _players[i].getName() << " has won the game!" << endl;
            cout << "=============================================" << endl;
            return true;
        }
    }
    return false;
}