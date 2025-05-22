#include <iostream>
#include "Player.h"
#include <vector>
// #include "Candystore.h"


using namespace std;



string lowercase2(string str)
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

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------


Player::Player()
{
    _stamina = 0;
    _candy_amount = 0;
    _gold = 0.0;
    _effect = "";
    _name = "No Name";
    _turns_lost = 0;
    for (int i = 0; i < _MAX_CANDY_AMOUNT; i++)
    {
        Candy candy;
        candy.name = "";
        candy.description = "";
        candy.price = 0.0;
        candy.candy_type = "";
        
        _inventory[i] = candy;
    }

}


Player::Player(int stamina, double gold, string effect, Candy candy_array[], const int CANDY_ARR_SIZE)
{
    _stamina = stamina;
    _gold = gold;
    _effect = effect;
    _candy_amount = 0;
    _name = "No Name";
    _turns_lost = 0;

    int j = 0;

    for (int i = 0; (i < CANDY_ARR_SIZE && i < _MAX_CANDY_AMOUNT); i++)
    {
        if (candy_array[i].name != "")
        {
            _inventory[j] = candy_array[i];
            j++;
            _candy_amount += 1;
        }
    }


}


Player::Player(int stamina, double gold, string effect, Candy candy_array[], const int CANDY_ARR_SIZE, string name)
{
    _stamina = stamina;
    _gold = gold;
    _effect = effect;
    _candy_amount = 0;
    _name = name;

    int j = 0;

    for (int i = 0; (i < CANDY_ARR_SIZE && i < _MAX_CANDY_AMOUNT); i++)
    {
        if (candy_array[i].name != "")
        {
            _inventory[j] = candy_array[i];
            j++;
            _candy_amount += 1;
        }
    }


}


void Player::setStamina(int stamina)
{
    _stamina = stamina;
}

int Player::getStamina() 
{
    return _stamina;
}

void Player::setGold(double gold)
{
    _gold = gold;
}

double Player::getGold() 
{
    return _gold;
}

void Player::setEffect(string effect)
{
    _effect = effect;
}

string Player::getEffect() 
{
    return _effect;
}

void Player::setName(string name)
{
    _name = name;
}

string Player::getName()
{
    return _name;
}

int Player::getNumber()
{
    return _number;
}


void Player::setNumber(int number)
{
    _number = number;
}


int Player::getPosition()
{
    return _position;
}


void Player::setPosition(int position)
{
    _position = position;
}


void Player::printInventory()
{
    int j = 0;
    for (int i = 0; i < 9; i++)
    {
        string name = _inventory[i].name;
        if (name == "")
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
    
}


Candy Player::findCandy(string candy_name)
{
    
    for (int i = 0; i < _MAX_CANDY_AMOUNT; i++)
    {
        if(lowercase2(_inventory[i].name) == lowercase2(candy_name))
        {
            return _inventory[i];
        }
    }

    Candy candy = {"","", "", 0, 0.0 ,""};
    return candy;
}


bool Player::addCandy(Candy candy)
{
    
    if (_inventory[_MAX_CANDY_AMOUNT-1].name != "")
    {
        return false;
    }

    int j = 0;
    for (int i = 0; i < _MAX_CANDY_AMOUNT; i++)
    {
        if (_inventory[i].name == "")
        {
            j = i;
            break;  
        }
    }
    _inventory[j].name = candy.name;
    _inventory[j].description = candy.description;
    _inventory[j].price = candy.price;
    _inventory[j].candy_type = candy.candy_type;

    _candy_amount += 1;
    return true;
}


bool Player::removeCandy(string candy_name)
{
    if(findCandy(candy_name).name == "")
    {
        return false;
    }

    Candy temp;
    for (int i = 0; i < _MAX_CANDY_AMOUNT; i++)
    {
        if (lowercase2(_inventory[i].name) == lowercase2(candy_name))
        {
            for (int j = i; j < _MAX_CANDY_AMOUNT -1; j++)
            {
                temp.name = _inventory[j+1].name;
                temp.description = _inventory[j+1].description;
                temp.price = _inventory[j+1].price;
                temp.candy_type = _inventory[j+1].candy_type;

                _inventory[j] = temp;
            }
            _inventory[_MAX_CANDY_AMOUNT - 1].name = "";
            _inventory[_MAX_CANDY_AMOUNT - 1].description = "";
            _inventory[_MAX_CANDY_AMOUNT - 1].price = 0.0;
            _inventory[_MAX_CANDY_AMOUNT - 1].candy_type = "";
            break;
        }
    }

    _candy_amount -= 1;

    return true;
}

// void Player::setCharacter(string name)
// {
//     _character = name;
// }

// struct Candy
// {
//     string name;
//     string description;
//     double price;
//     string candy_type;
// };


vector<Candy> Player::getInventory()
{
    int i = 0;
    vector<Candy> inventory;
    while (_inventory[i].name != "" && i < 9)
    {
        Candy candy;
        candy.name = _inventory[i].name;
        candy.description = _inventory[i].description;
        candy.price = _inventory[i].price;
        candy.candy_type = _inventory[i].candy_type;

        inventory.push_back(candy);
        i++;
    }

    return inventory;
}


void Player::emptyInventory()
{

    for (int i = 0; i < _MAX_CANDY_AMOUNT; i++)
    {
        _inventory[i].name = "";
        _inventory[i].description = "";
        _inventory[i].price = 0.0;
        _inventory[i].candy_type = "";
    }
}

int Player::getCandyAmount()
{
    return _candy_amount;
}

void Player::setCandyAmount(int amount)
{
    _candy_amount = amount;
}


vector<int> Player::getTilesMoved()
{
    return _tiles_moved;
}


void Player::setTilesMoved(vector<int> tiles_moved)
{
    emptyTilesMoved();
    for (int i = 0; i < int(tiles_moved.size()); i++)
    {
        addTileMoved(tiles_moved.at(i));
    }
}


void Player::addTileMoved(int num)
{
    _tiles_moved.push_back(num);
}


void Player::emptyTilesMoved()
{
    for (int i = 0; i < int(_tiles_moved.size()); i++)
    {
        _tiles_moved.pop_back();
    }
}


void Player::swapCandy(Candy candy2add, string candy2remove)
{
    removeCandy(candy2remove);
    addCandy(candy2add);
}


vector<Candy> Player::findCandyByEffect(string candy_type)
{
    vector<Candy> candies;
    for (int i = 0; i < _MAX_CANDY_AMOUNT; i++)
    {
        if(lowercase2(_inventory[i].candy_type) == lowercase2(candy_type))
        {
            candies.push_back(_inventory[i]);
        }
    }
    return candies;
}


string Player::getCharacter()
{
    return _character;
}


void Player::setCharacter(string name)
{
    _character = name;
}


void Player::setTurnsLost(int num)
{
    _turns_lost = num;
}


int Player::getTurnsLost()
{
    return _turns_lost;
}

