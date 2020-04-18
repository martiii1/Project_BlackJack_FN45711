#pragma once

#include "Deck.hpp"
#include "Player.hpp"
#include <fstream>

class BlackJack
{
public:
    void Start(); // Starts the game

    bool readPlayerData(); // displays the registered players(if there are none the function asks for a new user)
    void savePlayerData(); // Saves the new results to the file
    void getCommands(); // Waits for a command (Hit/Stand/Probability)


private:
    Deck fCardDeck;
    Player fPlayer;
    unsigned int fID;
    unsigned int fAcesInHand;


    void showRegisteredPlayers(std::ifstream &file);
    bool findPlayer(char *firstName,char *secondName);
    void loadPlayer(); // load existing player of registers a new one
    unsigned int strToInt(char *str);
    float strToFloat(char *str);
    void pickDeck();

    bool fHit(); // Draws a new card, checks the points(returns false if the game is lost)
    void fProbability(); // Returns the probability of the next drawn card to get the player to 21 points
    void fStand();
    unsigned short fDealersDraw();

    void fCreateNewPlayer();
    void fCreateNewPlayer(char *firstName, char *secondName,unsigned short int age, unsigned int id);


};