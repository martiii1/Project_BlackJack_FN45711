#pragma once

#include "CardInformation.hpp"

#define MAX_CARD_SERIALNUMBER_LENGHT 15
class Cards
{
public:
    Cards();
    void setCardSuit(Suit cardSuit);
    void setCardValue(CardValue cardValue);
    void setCardSerialNum(char* CardSerialNumber);
    void drawCard();
    void NotDrawnCard();

    bool isItDrawn(); // checks if the card is already drawn
    Suit getCardSuit() const;
    CardValue getCardValue() const;
    char* getCardSN() const;
    unsigned short int getCardPoints(); // returns the card points


    void printName(); // Prints the card in a readable way -> Ace of Spades
    void printPoints(); // Prints card points
private:
    Suit fCardSuit;
    CardValue fCardValue;
    char fCardSerialNumber[MAX_CARD_SERIALNUMBER_LENGHT + 1];
    bool fisDrawn;
};