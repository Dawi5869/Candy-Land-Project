#ifndef GAMES_H
#define GAMES_H
#include <iostream>
#include "Player.h"
#include "CandyStore.h"
// #include "Board.h"
#include <vector>

using namespace std;


struct Character
{
    string name;
    int stamina;
    double gold;
    vector<Candy> candies;
};





// -------------------------------------------------------------------

class Game
{
    private:
        const static int _MAX_NUM_PLAYERS = 8;
        Player _players[_MAX_NUM_PLAYERS];
        int _num_of_players;
        const static int _MAX_NUM_STORES = 3;
        CandyStore _stores[_MAX_NUM_STORES];
        vector<Candy> _candies;
        vector<Character> _characters;


    public:
        Game();
        void addPlayer(Player player);
        void setNumOfPlayers(int num_of_players);
        void removePlayer(string name);
        bool checkWinner(); // incomplete
        void playerTurn(Player player); // incomplete
        vector<Player> getPlayers();
        int getNumOfPlayers();
        void printPlayers();
        int playerIndexByName(string);

        //---------------------for loading the game---------------------

        void setCandies();
        Candy candyByName(string candy_name);
        
        void setCharacters();

        void printCandies();
        void fillCandyStores();

        //--------------------for beginning the game--------------------
        void gameStart();
        
        
        void displayCharacters();
        int findCharacterIndex(string character_name);
        // void removeCharacter(string character_name);
        Character characterByName(string name);



        

        //-----------------------for Player class-----------------------

        void setPlayerName(string player_name, string Name); // Done 
        void setPlayerEffect(string player_name, string Effect); // Done
        void setPlayerStamina(string player_name, int Stamina); // Done
        void setPlayerNumber(string player_name, int Number); // Done
        void setPlayerPosition(string player_name, int Position); // Done
        void setPlayerCandyAmount(string player_name, int CandyAmount); // Done
        void setPlayerGold(string player_name, double Gold); // Done
        int getPlayerPosition(string player_name); // Done

        int getPlayerStamina(string player_name); // done
        double getPlayerGold(string player_name); // done
        string getPlayerEffect(string player_name); // done
        // string getPlayerName(string player_name);
        void printPlayerInventory(string player_name); // done
        Candy findPlayerCandy(string player_name, string candy_name); // done
        bool addPlayerCandy(string player_name, Candy candy); // done
        bool removePlayerCandy(string player_name, string candy_name); // done
        vector<Candy> getPlayerInventory(string player_name); // done
        int getPlayerNumber(string player_name); // done
        void emptyPlayerInventory(string player_name); // done
        int getPlayerCandyAmount(string player_name); // done

        vector<int> getPlayerTilesMoved(string player_name);
        void setPlayerTilesMoved(string player_name, vector<int>);
        void addPlayerTileMoved(string player_name, int);
        void emptyPlayerTilesMoved(string player_name);

        string getPlayerCharacter(string player_name);
        void setPlayerCharacter(string player_name, string character);

        void setPlayerTurnsLost(string player_name, int num);
        int getPlayerTurnsLost(string player_name);
        vector<Candy> candyByEffect(vector<Candy> inventory, int effect_value, string candy_type);
        void SwapCandy(string player_name, Candy candy2add, string candy2remove);

        

        //-----------------------for CandyStore class-----------------------

        void setCandyStoreNumbers(); // Done

        // void addCandyStore(int store_number, CandyStore);
        void displayStoreCandies(int store_number, Player &player); // Done
        bool addStoreCandy(int store_number, Candy); // Done
        bool removeStoreCandy(int store_number, string candy_name); // Done
        void setStorePosition(int store_number, int position); // Done
        int getStorPosition(int store_number); // Done

        
        //-------------------------turn operations-------------------------

        //  void playTile(string tile_type, string player_name); 
        // void useCandy(string player_name, string candy_name, Board &board); -------> in board class now
        void printPlayerStats(string player_name);
        bool skipTurn(string player_name);





};

#endif

//name
//stamina
//gold
//effect
//inventory
//number
//position
//candy_amount