#include "Suit.hpp"


char* ValToTxt(int val)
{
    char valuetotxt[14][6] = { "none" ,
                               "Ace" ,
                               "Two" ,
                               "Three" ,
                               "Four" ,
                               "Five" ,
                               "Six" ,
                               "Seven" ,
                               "Eight" ,
                               "Nine" ,
                               "Ten" ,
                               "Jack" ,
                               "Queen" ,
                               "King" , };

    return valuetotxt[val];
}

char* SuitToTxt(int val)
{
    char suittotxt[5][8] = { "None",
                             "Club",
                             "Diamond",
                             "Heart",
                             "Spades" };

    return suittotxt[val];
}