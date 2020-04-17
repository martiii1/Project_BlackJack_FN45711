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

void Player::newPlayer(size_t newID)
{
    std::cout << "Enter your two names and age. " << std::endl;

    char inputInfo[MAX_LINE_LENGTH];
    std::cin.getline(inputInfo, MAX_LINE_LENGTH);

    fPlayerID = newID;
    char *token;
    //___________________________________________		First name \/
    token = strtok(inputInfo, " ");
    if (token == nullptr)
    {
        std::cout << "Invalid input! " << std::endl;
        delMem();
        return;
    }
    setFirstName(token);

    //___________________________________________		Second name \/
    token = strtok(nullptr, " ");

    if (token == nullptr)
    {
        std::cout << "Invalid input! " << std::endl;
        delMem();
        return;
    }
    setSecondName(token);

    //__________________________________________			Age		\/
    token = strtok(nullptr, " ");
    if (token == nullptr)
    {
        std::cout << "Invalid input! " << std::endl;
        delMem();
        return;
    }
    setAge(token);

    fGamesPlayed = 0;
    //__________________________________________
}

unsigned int Player::getPlayerID()
{
    return fPlayerID;
}

char* Player::getFirstName()
{
    return fFirstName;
}

char* Player::getSecondName()
{
    return fSecondName;
}

unsigned short int Player::getWins()
{
    return fWins;
}
unsigned short int Player::getAge()
{
    return fAge;
}

float Player::getWinrate()
{
    return fWinrate;
}

unsigned short int Player::getCurrentScore()
{
    return fCurrentScore;
}

unsigned int Player::strToInt(char* str)
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

void Player::delMem()
{
    delete[] fFirstName;
    delete[] fSecondName;
}

void Player::setPlayerID(unsigned int ID)
{
    fPlayerID = ID;
}

void Player::playAsPlayer(unsigned int ID)
{


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

void Player::writeInfoToFile(std::ofstream &file)
{
    file << fPlayerID << " ";
    file << fFirstName << " ";
    file << fSecondName << " ";
    file << fWins << " ";
    file << fWinrate << " ";
    file << fGamesPlayed << '\n';
}
