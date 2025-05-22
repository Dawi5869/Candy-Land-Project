#include "Candystore.h"
#include "Player.h"
// #include "Game.h"
#include <iostream>

using namespace std;



string lowercase(string str)
{
    string r_str = "";
    for (int i = 0; i < int(str.length()); i++)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
        {
            r_str += str[i] + 32;
        }
        else
        {
            r_str += str[i];
        }
    }

    return r_str;
}


//------------------------------------------------------------------------------------------------------

CandyStore::CandyStore()
{
    _number = 0;
    _position = 0;

    for (int i = 0; i < _MAX_CANDIES; i++)
    {
        Candy candy;
        candy.name = "";
        candy.description = "";
        candy.effect = "";
        candy.effect_value = 0;
        candy.price = 0.0;
        candy.candy_type = "";
        
        _candies[i] = candy;
    }
}

CandyStore::CandyStore(int number)
{
    _number = number;
    _position = 0;

    for (int i = 0; i < _MAX_CANDIES; i++)
    {
        Candy candy;
        candy.name = "";
        candy.description = "";
        candy.effect = "";
        candy.effect_value = 0;
        candy.price = 0.0;
        candy.candy_type = "";
        
        _candies[i] = candy;
    }
}

void CandyStore::displayCandies(Player &player)
{
    double min_price = 1000;
    cout << "Here is a list of the candies in the candy store." << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << "Name: " << _candies[i].name << endl;
        cout << "Description: " << _candies[i].description << endl;
        cout << "Effect: " << _candies[i].effect << endl;
        cout << "Effect value: " << _candies[i].effect_value << endl;
        cout << "Candy type: " << _candies[i].candy_type << endl;
        cout << "Price: " << _candies[i].price << endl;
        cout << "------------------------------------------------------" << endl;

        if(_candies[i].price < min_price)
        {
            min_price = _candies[i].price;
        }
    }

    cout << endl;
    cout << endl;

    if(min_price > player.getGold())
    {
        cout << "OH NO! You don't have enough gold to buy any candies at this store." << endl;
        return;
    }

    bool candy_baught = false;
    while (candy_baught == false)
    {
        cout << "Which candy would you like to buy?" << endl;
        string candy_choice;
        cin >> candy_choice;

        Candy candy = findCandy(candy_choice);

    
        if (!(player.getGold() >= candy.price))
        {
            cout << "You do not have enough gold to buy this candy" << endl;
        }
        else
        {
            vector<Candy> inventory = player.getInventory();
            if(inventory.at(int(inventory.size()) - 1).name != "")
            {
                cout << "Your inventory is full. Would you like to swap a candy?(y/n)" << endl;
                char choice;
                cin >> choice;

                if(choice == 'y')
                {
                    player.printInventory();
                    cout << "Which candy would you like to swap." << endl;
                    string swap_candy;
                    cin >> swap_candy;

                    player.swapCandy(candy, swap_candy);
                    cout << "You boaght the " << candy.name << " candy and swapped it for the " << swap_candy << " Candy." << endl;
                    player.setGold(player.getGold() - candy.price);
                    candy_baught = true;

                }
            }
            else
            {
                player.addCandy(candy);
                cout << "The " << candy.name << " candy has been added to your inventory." << endl;
                player.setGold(player.getGold() - candy.price);
                candy_baught = true;
            }
        }
    }

}

bool CandyStore::addCandy(Candy candy)
{
    
    if (_candies[_MAX_CANDIES-1].name != "")
    {
        return false;
    }

    int j = 0;
    for (int i = 0; i < _MAX_CANDIES; i++)
    {
        if (_candies[i].name == "")
        {
            j = i;
            break;  
        }
    }
    _candies[j].name = candy.name;
    _candies[j].description = candy.description;
    _candies[j].price = candy.price;
    _candies[j].candy_type = candy.candy_type;
    _candies[j].effect = candy.effect;
    _candies[j].effect_value = candy.effect_value;

    return true;
}

bool CandyStore::removeCandy(string candy_name)
{
    if(findCandy(candy_name).name == "")
    {
        return false;
    }

    Candy temp;
    for (int i = 0; i < _MAX_CANDIES; i++)
    {
        if (lowercase(_candies[i].name) == lowercase(candy_name))
        {
            for (int j = i; j < _MAX_CANDIES -1; j++)
            {
                temp.name = _candies[j+1].name;
                temp.description = _candies[j+1].description;
                temp.price = _candies[j+1].price;
                temp.candy_type = _candies[j+1].candy_type;
                temp.effect_value = _candies[j+1].effect_value;
                temp.effect = _candies[j+1].effect;

                _candies[j] = temp;
            }
            _candies[_MAX_CANDIES - 1].name = "";
            _candies[_MAX_CANDIES - 1].description = "";
            _candies[_MAX_CANDIES - 1].price = 0.0;
            _candies[_MAX_CANDIES - 1].candy_type = "";
            _candies[_MAX_CANDIES - 1].effect_value = 0;
            _candies[_MAX_CANDIES - 1].effect = "";
            break;
        }
    }


    return true;
}

void CandyStore::setPosition(int position)
{
    _position = position;
}

int CandyStore::getPosition()
{
    return _position;
}


Candy CandyStore::findCandy(string candy_name)
{
    
    for (int i = 0; i < _MAX_CANDIES; i++)
    {
        if(lowercase(_candies[i].name) == lowercase(candy_name))
        {
            return _candies[i];
        }
    }

    Candy candy{"","", "", 0, 0.0,""};
    return candy;
}