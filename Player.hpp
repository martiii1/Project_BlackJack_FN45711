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

    void newPlayer(size_t newID); // Gets a new line and splits it into tokens. Each token is saved accordingly.
    void newPlayer(char* firstName,char* secondName, unsigned short int age,unsigned int newID);

    unsigned int getPlayerID() const;
    char* getFirstName() const;
    char* getSecondName() const;
    unsigned short int getWins() const ;
    unsigned short int getAge() const;
    float getWinrate() const;
    unsigned short getPlayedGames() const;
    unsigned short int getCurrentScore() const ;

    void writeInfoToFile(std::ofstream &file); // Writes the current Player info to the file.


private:
    unsigned int fPlayerID;
    char *fFirstName;
    char *fSecondName;
    unsigned short int fAge;
    unsigned short int fWins;
    unsigned short int fGamesPlayed;
    float fWinrate;
    unsigned short int fCurrentScore;


    unsigned int strToInt(char *str); // Converts char* number to integer
    void delMem(); // deletes the dynamic names
};

