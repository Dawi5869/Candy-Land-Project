#include <iostream>
#include <vector>
#include "DeckOfCards.h"
#include <cstdlib>
#include <ctime>

using namespace std;

//16 cards of each color
//3 double color cards for each color

// struct Card
// {
//     string color;
//     bool x2;
// };


int calcRandom(int smaller, int larger)
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


DeckOfCards::DeckOfCards()
{
    _num_of_cards = 0;
}


void DeckOfCards::setCards()
{
    for (int i = 0; i < 16; i++)
    {
        Card card;
        card.color = "magenta";
        card.x2 = false;

        _cards.push_back(card);
        _num_of_cards += 1;
    }

    for (int i = 0; i < 16; i++)
    {
        Card card;
        card.color = "blue";
        card.x2 = false;

        _cards.push_back(card);
        _num_of_cards += 1;
    }

    for (int i = 0; i < 16; i++)
    {
        Card card;
        card.color = "green";
        card.x2 = false;

        _cards.push_back(card);
        _num_of_cards += 1;
    }

    for (int i = 0; i < 3; i++)
    {
        Card card;
        card.color = "magenta";
        card.x2 = true;

        _cards.push_back(card);
        _num_of_cards += 1;
    }

    for (int i = 0; i < 3; i++)
    {
        Card card;
        card.color = "blue";
        card.x2 = true;

        _cards.push_back(card);
        _num_of_cards += 1;
    }

    for (int i = 0; i < 3; i++)
    {
        Card card;
        card.color = "green";
        card.x2 = true;

        _cards.push_back(card);
        _num_of_cards += 1;
    }
}

Card DeckOfCards::drawCard()
{
    int index = calcRandom(0,_num_of_cards - 1);
    Card card;
    card.color = _cards.at(index).color;
    card.x2 = _cards.at(index).x2;

    Card temp;
    for (int i = index; i < (int(_cards.size()) - 1); i++)
    {
        _cards.at(i).color = _cards.at(i+1).color;
        _cards.at(i).x2 = _cards.at(i+1).x2;
    }
    _cards.pop_back();

    _num_of_cards -= 1;

    return card;
}

int DeckOfCards::getNumOfCards()
{
    return _num_of_cards;
}
