#pragma once

#include "Deck.hpp"
#include "Player.hpp"
#include <fstream>

class BlackJack
{
public:
    void Start();

    bool readPlayerData();
    void savePlayerData();
    void getCommands();


private:
    Deck fCardDeck;
    Player fPlayer;
    unsigned int fID;
    unsigned int fAcesInHand;


    void showRegisteredPlayers(std::ifstream &file);
    bool findPlayer(char *firstName,char *secondName);
    bool loadPlayer();
    unsigned int strToInt(char *str);
    float strToFloat(char *str);
    void pickDeck();

    bool fHit();
    void fProbability();
    void fStand();
    unsigned short fDealersDraw();

    void fCreateNewPlayer();


};