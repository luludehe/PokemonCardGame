//
// Created by lucas on 15/12/23.
//
#include <string>
using namespace std;

#ifndef POKEMON_POKEMON_H
#define POKEMON_POKEMON_H

class Card {
public:
    Card(std::string name);
    virtual void displayInfo() = 0;
    string getCardName();
private:
    std::string CardName;
};

#endif //POKEMON_POKEMON_H
