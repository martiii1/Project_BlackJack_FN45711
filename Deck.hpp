#pragma once
#include<cstring>

#include "Deck.hpp"
#include "Cards.hpp"

#define MAX_DECK_SERIALNUMBER_LENGHT 10

class Deck
{
public:
    Deck();
    ~Deck();
    Deck(const Deck& other);
    Deck& operator=(const Deck& other);

    void newDefaultDeck();
    void newCustomDeck(unsigned short int sizeOfDeck, char* deckSeries);
    void printCards() const;
    void shuffleCard(int numberOfTimes);
    void swapCards(int first,int second);
    int drawCards(bool allCards);

    int draw();

    int suitCount(Suit cardSuit);
    int rankCounter(unsigned int points);
    unsigned short int getUndrawnCards();

private:
    unsigned short int fNumberOfCards;
    char fDeckSerialNumber[MAX_DECK_SERIALNUMBER_LENGHT + 1];
    Cards* fCards;


    char* newSerialNumber();
    void copyDeck(const Deck& other);
    void delDeckMem();

};