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

    void newDefaultDeck(); // Creates a new deck with 52 Cards and series = "Default"
    void newCustomDeck(unsigned short int sizeOfDeck, char* deckSeries); // Creates a deck with custom length and series
    void printCards() const; // Test function that prints all cards in the deck
    void shuffleCard(int numberOfTimes); // Shuffles the deck X number of time
    void swapCards(int first,int second); // Swaps cards on positions "first" and "second"
    int drawCards(bool allCards); // Draws a card and prints the names of all drawn cards or newly drawn cards(dealer's)
                                  //returns the card points

    int suitCount(Suit cardSuit); // This is the suit_count function form the tasks given (returns the number of cards with that Suit)
    int rankCounter(unsigned int points); // The rank_count function form the tasks given (returns the NOT Drawn cards with that point value)
    unsigned short int getNotDrawnCards(); // Returns how many cards from the deck aren't drawn.

private:
    unsigned short int fNumberOfCards;
    char fDeckSerialNumber[MAX_DECK_SERIALNUMBER_LENGHT + 1];
    Cards* fCards;


    char* newSerialNumber();
    void copyDeck(const Deck& other);
    void delDeckMem();

};