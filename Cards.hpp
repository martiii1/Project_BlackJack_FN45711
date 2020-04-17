#pragma once

#include "Suit.hpp"
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

    bool isItDrawn();
    Suit getCardSuit() const;
    CardValue getCardValue() const;
    char* getCardSN() const;
    unsigned short int getCardPoints();


    void printName();
    void printPoints();
private:
    Suit fCardSuit;
    CardValue fCardValue;
    char fCardSerialNumber[MAX_CARD_SERIALNUMBER_LENGHT + 1];
    bool fisDrawn;
};