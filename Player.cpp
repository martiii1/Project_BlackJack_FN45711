#include "Player.hpp"
#include <cstring>
#include <iostream>

#pragma warning(disable:4996)
#define MAX_LINE_LENGTH 50

Player::Player()
{
    fPlayerID = 0;
    fFirstName = nullptr;
    fSecondName = nullptr;
    fAge = 0;
    fWins = 0;
    fWinrate = 0;
    fCurrentScore = 0;
}

Player::~Player()
{
    delMem();
}

void Player::setFirstName(char* name)
{
    fFirstName = new(std::nothrow) char[strlen(name) + 1]; /// +1 because of \0
    if (fFirstName == nullptr)
    {
        std::cout << "Not enough memory! " << std::endl;
        return;
    }

    strcpy(fFirstName, name);
}

void Player::setSecondName(char* name)
{
    fSecondName = new(std::nothrow) char[strlen(name) + 1]; /// +1 because of \0
    if (fSecondName == nullptr)
    {
        std::cout << "Not enough memory! " << std::endl;
        return;
    }
    strcpy(fSecondName, name);
}

void Player::setWins(unsigned short int wins)
{
    fWins = wins;
}

void Player::setAge(unsigned short int age)
{
    fAge = age;
}

void Player::setAge(char* age)
{
    unsigned int tempAge = strToInt(age);
    if (tempAge < 18)
    {
        std::cout << "You are too young to play BlackJack" << std::endl;
        delMem();
        return;
    }
    if (tempAge > 90)
    {
        std::cout << "You are too old to play BlackJack" << std::endl;
        delMem();
        return;
    }

    fAge = tempAge;
}

void Player::setWinrate(float winrate)
{
    fWinrate = winrate;
}

void Player::setCurrentScore(unsigned short int score)
{
    fCurrentScore = score;
}

void Player::newPlayer(size_t newID) // Gets a new line and splits it into tokens. Each token is saved accordingly.
{
    bool correctInput = false;
    char inputInfo[MAX_LINE_LENGTH];

    while(!correctInput) // Doesn't continue if the input is not correct(or expected)
    {
        correctInput = true;
        std::cout << "Enter your two names and age. " << std::endl;

        std::cin.getline(inputInfo, MAX_LINE_LENGTH);

        fPlayerID = newID;
        char *token;

        token = strtok(inputInfo, " ");// Expects First Name
        if (token == nullptr)
        {
            std::cout << "Invalid input! " << std::endl;
            correctInput = false;
            continue;
        }
        setFirstName(token);


        token = strtok(nullptr, " ");// Expects Second Name
        if (token == nullptr)
        {
            std::cout << "Invalid input! " << std::endl;
            correctInput = false;
            continue;
        }
        setSecondName(token);


        token = strtok(nullptr, " "); // Expects Age
        if (token == nullptr)
        {
            std::cout << "Invalid input! " << std::endl;
            correctInput = false;
            continue;
        }
        setAge(token);

        fGamesPlayed = 0; // Zeroes the new player's games
    }

}

unsigned int Player::getPlayerID() const
{
    return fPlayerID;
}

char* Player::getFirstName() const
{
    return fFirstName;
}

char* Player::getSecondName() const
{
    return fSecondName;
}

unsigned short int Player::getWins() const
{
    return fWins;
}
unsigned short int Player::getAge() const
{
    return fAge;
}

float Player::getWinrate() const
{
    return fWinrate;
}

unsigned short int Player::getCurrentScore() const
{
    return fCurrentScore;
}

unsigned int Player::strToInt(char* str) // Converts char* number to integer
{
    unsigned int number=0;
    char c;
    unsigned int multiplier = 1;
    size_t counter = strlen(str);

    for (int i = counter - 1; i >= 0; i--)
    {
        number += (str[i] - '0') * multiplier;
        multiplier *= 10;
    }

    return number;
}

void Player::delMem() // deletes the dynamic memory
{
    delete[] fFirstName;
    delete[] fSecondName;
}

void Player::setPlayerID(unsigned int ID)
{
    fPlayerID = ID;
}

void Player::newPlayer(char *firstName, char *secondName, unsigned short age, unsigned int newID)
{
    setFirstName(firstName);
    setSecondName(secondName);
    fAge = age;
    fPlayerID = newID;
    fGamesPlayed = 0;
}

void Player::setPlayedGames(unsigned short gamesPlayed)
{
    fGamesPlayed = gamesPlayed;
}

unsigned short Player::getPlayedGames() const
{
    return fGamesPlayed;
}

void Player::writeInfoToFile(std::ofstream &file) // Writes the current Player info to the file.
{
    file << fPlayerID << " ";
    file << fFirstName << " ";
    file << fSecondName << " ";
    file << fWins << " ";
    file << fWinrate << " ";
    file << fGamesPlayed << '\n';
}
