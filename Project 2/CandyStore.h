#ifndef CANDYSTORE_H
#define CANDYSTORE_H
#include <iostream>
#include "Player.h"
// #include "Game.h"

using namespace std;


// struct Candy
// {
//     string name;
//     string description;
//     string effect;
//     int effect_value;
//     double price;
//     string candy_type;
// };


class CandyStore
{
    private:
        int _number;
        const static int _MAX_CANDIES = 3;
        Candy _candies[3];
        int _position;



    public:
        CandyStore();
        CandyStore(int number);
        void displayCandies(Player &player); 
        bool addCandy(Candy candy);
        bool removeCandy(string candy_name);
        void setPosition(int position);
        int getPosition();
        Candy findCandy(string candy_name);


};

#endif