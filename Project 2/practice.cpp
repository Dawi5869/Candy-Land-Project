#include <iostream>
#include <cstdlib>
#include <ctime>
// #include "DeckOfCards.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Character
{
    string name;
    int stamina;
    double gold;
    vector<string> candies;
};


int calcRandom2(int smaller, int larger)
{
    srand(time(0));
    
    int diff = (larger+1) - smaller;
    cout << "diff: " << diff << endl;
    int random = (rand() % diff) + smaller;
    return random;
}


int main()
{
    // ifstream test_file;
    // test_file.open("Characters.txt");

    // vector<Character> characters;

    // string line;
    // while (getline(test_file, line))
    // {
    //     // character name|stamina|gold|candies
        
    //     stringstream ss(line);
        
    //     Character character;

    //     getline(ss, character.name, '|');

    //     string stamina;
    //     getline(ss, stamina, '|');
    //     cout << "---" << stamina << "---" << endl;
    //     character.stamina = stoi(stamina);

    //     string gold;
    //     getline(ss, gold, '|');
    //     character.gold = stod(gold);

    //     string candies;
    //     getline(ss, candies);
    //     stringstream ss2;
    //     ss2 << candies;

    //     string candy;
        
    //     while(getline(ss2, candy, ','))
    //     {
    //         // cout << candy << endl;
    //         character.candies.push_back(candy);
    //     }

    //     characters.push_back(character);
        
    // }

    // for(int i = 0; i < int(characters.size()); i++)
    // {
        
    //     for (int j = 0; j < int(characters.at(i).candies.size()); j++)
    //     {
    //         cout << characters.at(i).candies.at(j) << endl;
    //     }
    //     cout << endl;
    // }


    // test_file.close();

    vector<int> test1 = {1,2,3,4,5};
    vector<int> test2 = test1;

    cout << "test1 values" << endl;
    for (int i = 0; i < int(test1.size()); i++)
    {
        cout << test1.at(i) << endl;
    }

    cout << "test2 values" << endl;
    for (int i = 0; i < int(test1.size()); i++)
    {
        cout << test2.at(i) << endl;
    }



    return 0;
}