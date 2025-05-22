#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <vector>
// #include "Candystore.h"


using namespace std;

struct Candy
{
    string name;
    string description;
    string effect;
    int effect_value;
    double price;
    string candy_type;
};

class Player
{
    private:
        const static int _MAX_CANDY_AMOUNT = 9;
        int _stamina;
        double _gold;
        string _effect;
        Candy _inventory[_MAX_CANDY_AMOUNT];
        int _candy_amount;
        int _number = 0;
        string _name;
        int _position;
        vector<int> _tiles_moved;
        string _character;
        int _turns_lost;
        

    public:
        Player();
        Player(int stamina, double gold, string effect, Candy candy_array[], const int CANDY_ARR_SIZE);
        Player(int stamina, double gold, string effect, Candy candy_array[], const int CANDY_ARR_SIZE, string name);
        void setStamina(int stamina);  // added to game class
        int getStamina(); // added to game class
        void setGold(double gold); // added to game class
        double getGold(); // added
        void setEffect(string effect); // added to game class
        string getEffect(); // added
        void setName(string name); // added to game class
        string getName(); // added
        void printInventory(); // added
        Candy findCandy(string candy_name); // added
        bool addCandy(Candy candy); // added
        bool removeCandy(string candy_name); // added
        vector<Candy> getInventory(); // added
        int getNumber(); // added
        void setNumber(int number); // added to game class
        void emptyInventory(); // added
        int getPosition(); // added
        void setPosition(int position); // added to game class
        int getCandyAmount(); // added
        void setCandyAmount(int amount); // added to game class

        void swapCandy(Candy candy2add, string candy2remove);
        vector<Candy> findCandyByEffect(string candy_type);
        

        vector<int> getTilesMoved(); // added
        void setTilesMoved(vector<int>); // added
        void addTileMoved(int); // added
        void emptyTilesMoved(); // added

        string getCharacter();
        void setCharacter(string name);
        // void setCharacter(string name);

        void setTurnsLost(int num);
        int getTurnsLost();

        
};







#endif