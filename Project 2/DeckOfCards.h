#ifndef DECKOFCARDS_H
#define DECKOFCARDS_H
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;


struct Card
{
    string color;
    bool x2;
};


class DeckOfCards
{
    private:
        vector<Card> _cards;
        int _num_of_cards;


    public:
        DeckOfCards();
        void setCards();
        Card drawCard();
        int getNumOfCards();
        
};

#endif