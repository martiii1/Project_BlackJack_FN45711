#include "Cards.hpp"
#include <cstring>
#include <iostream>

#pragma warning(disable:4996)
#define MAX_TXT_BUFFER 50

Cards::Cards()
{
    fCardSuit = Suit::None;
    fCardValue = CardValue::none;
    strcpy(fCardSerialNumber, "\0");
    fisDrawn = false;
}

void Cards::setCardSuit(Suit cardSuit)
{
    fCardSuit = cardSuit;
}

void Cards::setCardValue(CardValue cardValue)
{
    fCardValue = cardValue;
}

void Cards::setCardSerialNum(char* CardSerialNumber)
{
    strcpy(fCardSerialNumber, CardSerialNumber);

}

void Cards::drawCard()
{
    fisDrawn = true;
}

void Cards::NotDrawnCard()
{
    fisDrawn = false;
}

bool Cards::isItDrawn() const // checks if the card is already drawn
{
    return fisDrawn;
}

Suit Cards::getCardSuit() const
{
    return fCardSuit;
}

CardValue Cards::getCardValue() const
{
    return fCardValue;
}

char* Cards::getCardSN() const
{
    char* temp = new char[MAX_CARD_SERIALNUMBER_LENGHT+1];
    strcpy(temp, fCardSerialNumber);

    return temp;
}

unsigned short int Cards::getCardPoints() // returns the card points
{
    if ((int)fCardValue >= (int)CardValue::two && (int)fCardValue <= (int)CardValue::ten)
        return (int)fCardValue;
    if ((int)fCardValue >= (int)CardValue::jack && (int)fCardValue <= (int)CardValue::king)
        return 10; // jack, queen, king = 10pt
    if ((int)fCardValue == (int)CardValue::ace)
        return 11;

}

void Cards::printName() const // Prints the card in a readable way -> Ace of Spades
{
    char temp[MAX_TXT_BUFFER];

    strcpy(temp, ValToTxt((int)getCardValue())); // converts the "Value" to words
    std::cout << temp << " of ";

    strcpy(temp, SuitToTxt((int)getCardSuit())); // converts the "Suit" to words
    std::cout << temp << "s   ";
}

void Cards::printPoints() // Prints card points
{
    short int temp = getCardPoints();

    if(temp == 11)
        std::cout << "  (Points: 1 or 11)";
    else
        std::cout << "  (Points: " << temp << ")";
}