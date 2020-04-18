#include "Deck.hpp"
#include<iostream>
#include "Cards.hpp"
#include "Suit.hpp"
#include <time.h>

#pragma warning(disable:4996)
#define MAX_TXT_BUFFER 8

Deck::Deck()
{
    fNumberOfCards = 0;
    strcpy(fDeckSerialNumber, "\0");
    fCards = nullptr;
}

Deck::~Deck()
{
    delDeckMem();
}

Deck::Deck(const Deck& other)
{
    if(this != &other)
        copyDeck(other);

}

Deck& Deck::operator=(const Deck& other)
{
    if (this != &other)
    {
        delDeckMem();
        copyDeck(other);
    }

    return *this;
}

void Deck::newDefaultDeck()
{
    newCustomDeck(52, "Default");

}

void Deck::newCustomDeck(unsigned short int sizeOfDeck, char* deckSeries)
{
    if(strcmp(deckSeries,"") == 0)
        strcpy(deckSeries,"Custom");

    if (strlen(deckSeries) > MAX_DECK_SERIALNUMBER_LENGHT)
    {
        std::cout << "Deck series too long! " << std::endl;
        return;
    }

    fNumberOfCards = sizeOfDeck;
    strcpy(fDeckSerialNumber, deckSeries);

    fCards = new(std::nothrow) Cards[fNumberOfCards];
    if (fCards == nullptr)
    {
        std::cout << "Not enough memory! " << std::endl;
        return;
    }

    size_t counter = 0;
    char tempCardSN[MAX_CARD_SERIALNUMBER_LENGHT];
    strcpy(tempCardSN, fDeckSerialNumber);
    strcat(tempCardSN, newSerialNumber());

    size_t maxRepeatsPerCard = (sizeOfDeck - 1) / 52 + 1;
    bool flag = false;

    for (int i = 0; i < maxRepeatsPerCard; i++)
    {
        for (int s = (int)Suit::Club; s <= (int)Suit::Spades; s++)
        {
            for (int v = (int)CardValue::ace; v <= (int)CardValue::king; v++)
            {
                fCards[counter].setCardValue((CardValue)v);
                fCards[counter].setCardSuit((Suit)s);
                fCards[counter].setCardSerialNum(tempCardSN);
                fCards[counter].NotDrawnCard();

                strcpy(tempCardSN, fDeckSerialNumber);
                strcat(tempCardSN, newSerialNumber());

                counter++;
                if (counter == fNumberOfCards)
                {
                    flag = true;
                    break;
                }
            }

            if (flag == true)
                break;
        }

        if (flag == true)
            break;
    }

}


void Deck::printCards() const // Test function that prints all cards in the deck
{
    char temp[MAX_TXT_BUFFER];
    for (int i = 0; i < fNumberOfCards; i++)
    {
        strcpy(temp, ValToTxt((int)fCards[i].getCardValue()));
        std::cout << temp << " of ";
        strcpy(temp, SuitToTxt((int)fCards[i].getCardSuit()));
        std::cout << temp << "s  ";
        std::cout << "SN: " << fCards[i].getCardSN();
        std::cout << std::endl;
    }
}

void Deck::shuffleCard(int numberOfTimes) // Shuffles the deck X number of time
{
    srand(time(NULL));
    int randomNum = rand() % fNumberOfCards;

    for(int j=0;j<numberOfTimes;j++)
    {
        for (int i = 0; i < fNumberOfCards; i++)
        {
            swapCards(i, randomNum);
            randomNum = rand() % fNumberOfCards;
        }
    }

}

void Deck::swapCards(int first, int second) // Swaps cards on positions "first" and "second"
{
    if(first >= 0 && first <fNumberOfCards)
        if (second >= 0 && second < fNumberOfCards)
        {

            Cards temp;

            temp = fCards[first];

            fCards[first] = fCards[second];
            fCards[second] = temp;

            return;
        }

    std::cout << "Invalid cards!" << std::endl;
}


int Deck::drawCards(bool allCards) // Draws the top car (that isn't already drawn) and prints the names of
                                  // all drawn cards(the player's hand) or newly drawn cards(dealer's hand)
{
    for(int i=0;i<fNumberOfCards;i++)
    {
        if(allCards) // every drawn card
            fCards[i].printName();

        if(!fCards[i].isItDrawn()) // If the card isn't drawn
        {
            if(!allCards) // only the current card that is drawn
             fCards[i].printName(); // Prints the card

            fCards[i].drawCard();
            return fCards[i].getCardPoints(); // returns the card points
        }

    }

}



char* Deck::newSerialNumber()
{
    static char serialCreator[6] = { 'a','a','a','a','a' };

    static char first = 'a';
    static char second = 'a';
    static char third = 'a';
    static char fourth = 'a';
    static char fifth = 'a';

    serialCreator[0] = first;
    serialCreator[1] = second;
    serialCreator[2] = third;
    serialCreator[3] = fourth;
    serialCreator[4] = fifth;

    if (fifth == 'z')
    {
        fifth = 'a';
        if (fourth == 'z')
        {
            fourth = 'a';
            if (third == 'z')
            {
                third = 'a';
                if (second == 'z')
                {
                    second = 'a';
                    if (first == 'z')
                    {
                        return nullptr;
                    }
                    else
                    {
                        first++;
                    }
                }
                else
                {
                    second++;
                }
            }
            else
            {
                third++;
            }
        }
        else
        {
            fourth++;
        }
    }
    else
    {
        fifth++;
    }

    return serialCreator;
}

void Deck::copyDeck(const Deck& other)
{
    fCards = new(std::nothrow) Cards[other.fNumberOfCards];
    if (fCards == nullptr)
    {
        std::cout << "Error while allocating data! " << std::endl;
        delDeckMem();
        return;
    }

    fNumberOfCards = other.fNumberOfCards;
    strcpy(fDeckSerialNumber, other.fDeckSerialNumber);

    for (int i = 0; i < fNumberOfCards; i++)
    {
        fCards[i] = other.fCards[i];
    }

}

void Deck::delDeckMem()
{
    delete[] fCards;
}

int Deck::suitCount(Suit cardSuit) // This is the suit_count function form the tasks given (returns the number of cards with that Suit)
{
    unsigned short int counter=0;
    for(int i=0;i<fNumberOfCards;i++)
    {
        if(fCards[i].isItDrawn() == false)
            if(fCards[i].getCardSuit() == cardSuit)
                counter++;
    }

    return counter;
}

int Deck::rankCounter(unsigned int points) // The rank_count function form the tasks given (returns the NOT Drawn cards with that point value)
{
    unsigned short int counter=0;
    for(int i=0;i<fNumberOfCards;i++)
    {
        if(fCards[i].isItDrawn() == false)
        {
            if(points == 1)
            {
                if (fCards[i].getCardPoints() == 11)
                    counter++;
            }
            else
            {
                if (fCards[i].getCardPoints() == points)
                    counter++;
            }
        }
    }

    return counter;
}

unsigned short int Deck::getNotDrawnCards() // Returns how many cards from the deck aren't drawn.
{
    unsigned short int counter=0;
    for(int i=0;i<fNumberOfCards;i++)
    {
        if(fCards[i].isItDrawn() == false)
            counter++;
    }

    return  counter;
}
