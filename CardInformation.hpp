#pragma once

char* ValToTxt(int val);
char* SuitToTxt(int val);

enum class Suit
{
    None,
    Club,
    Diamond,
    Heart,
    Spades
};

enum class CardValue
{
    none=0,
    ace,
    two,
    three,
    four,
    five,
    six,
    seven,
    eight,
    nine,
    ten,
    jack,
    queen,
    king

};
