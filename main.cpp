#include "BlackJack.hpp"
#include <iostream>
//Github repo https://github.com/martiii1/Project_BlackJack_FN45711
//Martin Dimitrov FN45711 group6

int main()
{
    BlackJack Game;

    Game.Start();


    std::cin.get();
    std::cout << "\n \n \nPress any key to exit! ";
    std::cin.get();

    return 0;
}