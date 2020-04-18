#include "BlackJack.hpp"
#include "Player.hpp"
#include <fstream>
#include <iostream>
#include <cstring>

#define MAX_LINE_LENGTH 50
#define MAX_COMMAND_LENGTH 12

#define FILENAME "Players.txt"

void BlackJack::Start()
{
    fID = 0;
    fAcesInHand=0;


    if(!readPlayerData())
    {
        pickDeck();
    }
    else
    {
        if (loadPlayer())
        {
            pickDeck();
        }
        else
        {
            std::cout << "You can create a new player." << std::endl;
            fPlayer.newPlayer(fID);
            pickDeck();
        }
    }

    getCommands();



    savePlayerData();

}

bool BlackJack::readPlayerData() // displays the registered players(if there are none the function asks for a new user)
{
    std::ifstream readPlayerFile;
    readPlayerFile.open(FILENAME);

    if (!readPlayerFile.is_open()) // if the file can't be opened/doesn't exist the program ask for a new player
    {
        readPlayerFile.close();
        fCreateNewPlayer(); // asks for the new player's info
        return false; // returns false because the file wasn't found
    }
    else
    {
        showRegisteredPlayers(readPlayerFile); // Shows a list of registered players
        readPlayerFile.close();
        return true; // returns true because the file was found
    }


}

void BlackJack::savePlayerData()
{
    std::ifstream readFile;
    readFile.open(FILENAME);

    if (readFile.is_open())
    {
        int tempFlag;
        std::ofstream writeFile;
        writeFile.open("tempFile.txt");

        unsigned int ID;

        readFile >> ID;

        char tempLine[MAX_LINE_LENGTH];
        while (ID != fPlayer.getPlayerID())
        {
            if (writeFile.is_open())
            {
                tempFlag = ID;
                writeFile << ID;
                readFile.getline(tempLine, MAX_LINE_LENGTH);
                writeFile << tempLine << '\n';

                readFile >> ID;
                if(ID == tempFlag)
                    break;
            }
            else
            {
                std::cout << "Unexpected error!" << std::endl;
            }
        }

        fPlayer.setWinrate((float)fPlayer.getWins() / (float)fPlayer.getPlayedGames());

        fPlayer.writeInfoToFile(writeFile);


        readFile.ignore(MAX_LINE_LENGTH,'\n'); // Ignore This Player

        readFile.getline(tempLine, MAX_LINE_LENGTH);
        while (!readFile.eof())
        {
            if (writeFile.is_open())
            {
                writeFile << tempLine << '\n';
                readFile.getline(tempLine, MAX_LINE_LENGTH);
            }
            else
            {
                std::cout << "Unexpected error!" << std::endl;
            }
        }


        readFile.close();
        remove(FILENAME);
        writeFile.close();
        if (rename("tempFile.txt", FILENAME) != 0)
        {
            std::cout << "Unexpected error!" << std::endl;
        }


        std::cout << std::endl << "Player information successfully saved to the file! " << std:: endl;
    }
    else
    {
        std::ofstream writeFile;
        writeFile.open(FILENAME);
        if (writeFile.is_open())
        {
            fPlayer.writeInfoToFile(writeFile);////////////////////////////////////////////////////////////////////////////////
        }
        else
        {
            std::cout << "Unexpected error!" << std::endl;
        }


        writeFile.close();
        std::cout << std::endl << "Player information successfully saved to the file! " << std:: endl;
    }
}

void BlackJack::showRegisteredPlayers(std::ifstream &file)
{
    char tempBuffer[MAX_LINE_LENGTH];
    while (!file.eof())
    {
        file >> tempBuffer; // Ignores the "ID"
        file >> tempBuffer; // First name
        std::cout << tempBuffer << "  ";
        file >> tempBuffer; // Second name
        std::cout << tempBuffer <<"  ";
        file >> tempBuffer; // wins
        std::cout << tempBuffer << "  ";
        file >> tempBuffer; // winrate
        std::cout << tempBuffer << std::endl;
        file >> tempBuffer; // Ignore played games
        fID++;
    }
}

bool BlackJack::loadPlayer()
{
    char *token;
    char *firstName;
    char *secondName;

    char input[MAX_LINE_LENGTH];
    std::cout << "Choose a player or enter a new one." << std::endl;
    std::cin.getline(input, MAX_LINE_LENGTH);


    token = strtok(input, " ");
    if (token == nullptr)
    {
        //std::cout << "Error!" << std::endl;
        return false;
    }
    firstName = token;


    token = strtok(nullptr, " ");
    if (token == nullptr)
    {
        //std::cout << "Error!" << std::endl;
        return false;
    }
    secondName = token;

    token = strtok(nullptr, " ");
    if (token != nullptr)
    {
        std::cout << "Player not found." << std::endl;
        return false;
    }

    if (findPlayer(firstName, secondName) == true)
    {
        return true;
    }
    else
    {
        std::cout << "Player not found." << std::endl;
        return false;
    }

}

bool BlackJack::findPlayer(char *firstName, char *secondName)
{
    std::ifstream readFile(FILENAME);
    if (!readFile.is_open())
    {
        std::cout << "Error while reading " << FILENAME << std::endl;
        return false;
    }

    char temp[MAX_LINE_LENGTH];

    readFile.getline(temp, MAX_LINE_LENGTH);
    while (!readFile.eof())
    {


        char *token;
        char *fName;
        char *sName;
        unsigned int tempID;

        token = strtok(temp, " ");
        tempID = strToInt(token);

        token = strtok(nullptr, " ");
        if (token == nullptr)
        {
            std::cout << "Error!" << std::endl;
            return false;
        }
        fName = token;


        token = strtok(nullptr, " ");
        if (token == nullptr)
        {
            std::cout << "Error!" << std::endl;
            return false;
        }
        sName = token;


        if (strcmp(fName, firstName) == 0 && strcmp(sName, secondName) == 0)
        {
            std::cout << "You will play as: " << fName << " " << sName << ". ";
            fPlayer.setFirstName(fName);
            fPlayer.setSecondName(sName);
            fPlayer.setPlayerID(tempID);
            fPlayer.setCurrentScore(0);

            unsigned short int tempNum;

            token = strtok(nullptr, " ");
            tempNum = strToInt(token);

            fPlayer.setWins(tempNum);

            token = strtok(nullptr, " ");
            tempNum = strToFloat(token);

            fPlayer.setWinrate(tempNum);

            token = strtok(nullptr, " ");
            tempNum = strToInt(token);
            fPlayer.setPlayedGames(tempNum);
            


            readFile.close();

            return true;
        }

        readFile.getline(temp, MAX_LINE_LENGTH);
    }

    readFile.close();
    return false;
}

unsigned int BlackJack::strToInt(char *str)
{
    unsigned int number = 0;
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

void BlackJack::pickDeck()
{
    std::cout << "Choose the size of the deck: ";

    size_t deckSize;

    std::cin >> deckSize;

    if (deckSize < 52)
    {
        while (deckSize < 52)
        {
            std::cout << std::endl << "  You can't play with less then one deck of cards! Enter another size: ";
            std::cin >> deckSize;
        }
    }
    else if (deckSize == 52)
    {
        fCardDeck.newDefaultDeck();
    }
    else
    {
        std::cout << "Enter a custom deck series(\"Custom\" by default): ";
        char tempDeckSeries[MAX_DECK_SERIALNUMBER_LENGHT];

        std::cin.get();
        std::cin.getline(tempDeckSeries,MAX_DECK_SERIALNUMBER_LENGHT);

        fCardDeck.newCustomDeck(deckSize,tempDeckSeries);

    }

    fCardDeck.shuffleCard(5);
}

void BlackJack::getCommands()
{
    char tempCommand[MAX_COMMAND_LENGTH];

    fHit();
    std::cout <<"(Points: " << fPlayer.getCurrentScore() <<")" << std::endl;


    while(true)
    {

        std::cout << std::endl << "Hit/Stand/Probability" << std::endl;
        std::cin >> tempCommand;

        if (strcmp(tempCommand, "Hit") == 0)
        {
            if (fHit() == false)
            {
                std::cout << "(Points: " << fPlayer.getCurrentScore() << ")" << std::endl;

                std::cout << "You lost!" << std::endl;

                unsigned short int temp = fPlayer.getPlayedGames();
                fPlayer.setPlayedGames(temp + 1);
                return;
            }

            if (fPlayer.getCurrentScore() == 21)
            {
                std::cout << "(Points: " << fPlayer.getCurrentScore() << ")" << std::endl;

                std::cout << "You won!" << std::endl;

                unsigned short int temp = fPlayer.getPlayedGames();
                fPlayer.setPlayedGames(temp + 1);
                temp = fPlayer.getWins();
                fPlayer.setWins(temp + 1);
                return;
            }

            std::cout << "(Points: " << fPlayer.getCurrentScore() << ")" << std::endl;
        }

        if (strcmp(tempCommand, "Stand") == 0)
        {
            fStand();
            return;
        }

        if (strcmp(tempCommand, "Probability") == 0)
        {
            fProbability();
        }
    }

}

bool BlackJack::fHit()
{
    unsigned short int cardPoints;
    unsigned short int tempPoints = fPlayer.getCurrentScore();
    cardPoints = fCardDeck.drawCards(true);

    if(cardPoints == 11)
        fAcesInHand++;

    tempPoints = tempPoints + cardPoints;

    if (tempPoints > 21)
    {
        while(fAcesInHand != 0)
        {
            if(tempPoints > 21)
            {
                tempPoints -= 10;// counting an ace for 1 rather then 11
                fAcesInHand--;
            }
            else
            {
                break;
            }
        }

        if(tempPoints > 21)
        {
            fPlayer.setCurrentScore(tempPoints);
            return false;
        }
    }

    fPlayer.setCurrentScore(tempPoints);
    return true;
}

void BlackJack::fProbability()
{
    unsigned short int temp = 21-fPlayer.getCurrentScore();
    if(temp > 11)
        std::cout << 0;
    else
        std::cout << ((float)fCardDeck.rankCounter(temp) / (float) fCardDeck.getNotDrawnCards());

}

void BlackJack::fStand()
{
    unsigned  short int dealer;
    std::cout << "The dealer's draw: ";
    dealer = fDealersDraw();

    if(dealer <= fPlayer.getCurrentScore() || dealer > 21)
    {
        std::cout << "You win!" << std::endl;
        fPlayer.setWins(fPlayer.getWins() + 1);
        fPlayer.setPlayedGames(fPlayer.getPlayedGames() + 1);
    }
    else
    {
        std::cout << "You lost!" << std::endl;
        fPlayer.setPlayedGames(fPlayer.getPlayedGames() + 1);
    }


}

unsigned short BlackJack::fDealersDraw()
{
    unsigned short int playerPoints = fPlayer.getCurrentScore();
    unsigned short int dealerPoints = 0;
    fAcesInHand = 0;

    unsigned short int cardPoints;


    while(dealerPoints <= 17)
    {
        cardPoints = fCardDeck.drawCards(false);
        if(cardPoints == 11)
            fAcesInHand++;

        dealerPoints = dealerPoints + cardPoints;

        while(fAcesInHand != 0 && dealerPoints >17)
        {
                dealerPoints -= 10; // counting an ace for 1 rather then 11
                fAcesInHand--;
        }

    }

    std::cout <<" (Points: " << dealerPoints <<")" <<std::endl;
    return dealerPoints;
}

float BlackJack::strToFloat(char *str)
{

    float number = 0;
    char c;
    unsigned int multiplier = 1;
    unsigned int devisor = 1;
    size_t counter = strlen(str);

    for (int i = counter - 1; i >= 0; i--)
    {
        multiplier *= 10;
        if(str[i] == '.')
            devisor = multiplier;
        else
            number += (str[i] - '0') * multiplier;
    }

    number = number / devisor;

    return number;
}

void BlackJack::fCreateNewPlayer() // Gets all the information for a new player (First Name/Second Name/Age)
{
    std::cout << "There is no record of previous players. Please create a new player" << std::endl;

    fPlayer.newPlayer(fID);// Enter the player information into the Player class
    fID++; // Increases the player ID for the next entered player
}

