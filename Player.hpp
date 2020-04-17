#pragma once
#include <fstream>

class Player
{
public:
    Player();
    ~Player();
    void setFirstName(char* name);
    void setSecondName(char* name);

    void setWins(unsigned short int wins);
    void setAge(unsigned short int age);
    void setAge(char* age);
    void setWinrate(float winrate);
    void setPlayedGames(unsigned short int gamesPlayed);
    void setCurrentScore(unsigned short int score);
    void setPlayerID(unsigned int ID);

    void newPlayer(size_t newID);
    void newPlayer(char* firstName,char* secondName, unsigned short int age,unsigned int newID);
    void playAsPlayer(unsigned int ID);

    unsigned int getPlayerID();
    char* getFirstName();
    char* getSecondName();
    unsigned short int getWins();
    unsigned short int getAge();
    float getWinrate();
    unsigned short getPlayedGames() const;
    unsigned short int getCurrentScore();

    void writeInfoToFile(std::ofstream &file);


private:
    unsigned int fPlayerID;
    char *fFirstName;
    char *fSecondName;
    unsigned short int fAge;
    unsigned short int fWins;
    unsigned short int fGamesPlayed;
    float fWinrate;
    unsigned short int fCurrentScore;


    unsigned int strToInt(char *str);
    void delMem();
};

