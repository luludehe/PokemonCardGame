//
// Created by lucas on 15/12/23.
//
#include <string>
#include "../card.h"
using namespace std;

#ifndef POKEMON_ENERGYCARD_H
#define POKEMON_ENERGYCARD_H

class EnergyCard : public Card {
public:
    EnergyCard(string);
    void displayInfo();
    string getEnergyType();
private:
    string energyType;
};

#endif //POKEMON_ENERGYCARD_H
