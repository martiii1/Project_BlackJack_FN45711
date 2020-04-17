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


void Deck::printCards() const
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

void Deck::shuffleCard()
{
    srand(time(NULL));
    int randomNum = rand() % fNumberOfCards;
    for (int i = 0; i < fNumberOfCards; i++)
    {
        swapCards(i, randomNum);
        randomNum = rand() % fNumberOfCards;
    }

}

void Deck::swapCards(int first, int second)
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


int Deck::drawCards(bool allCards)
{
    for(int i=0;i<fNumberOfCards;i++)
    {
        if(allCards)
            fCards[i].printName();

        if(fCards[i].isItDrawn() == false)
        {
            if(!allCards)
             fCards[i].printName();

            fCards[i].drawCard();
            return fCards[i].getCardPoints();
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
        std::cout << "Error while alocating data! " << std::endl;
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

int Deck::suitCount(Suit cardSuit)
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

int Deck::rankCounter(unsigned int points)
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

int Deck::draw()
{
    Cards tempCard;

    tempCard = fCards[0];
    tempCard.printName();
    for(int i=1;i<fNumberOfCards;i++)
        swapCards(i-1,i);

    return  tempCard.getCardPoints();
}

unsigned short int Deck::getUndrawnCards()
{
    unsigned short int counter=0;
    for(int i=0;i<fNumberOfCards;i++)
    {
        if(fCards[i].isItDrawn() == false)
            counter++;
    }

    return  counter;
}
