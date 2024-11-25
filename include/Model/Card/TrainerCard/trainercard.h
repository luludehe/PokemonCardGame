//
// Created by lucas on 15/12/23.
//
#include <string>
#include "../card.h"
using namespace std;

#ifndef POKEMON_TRAINERCARD_H
#define POKEMON_TRAINERCARD_H

class TrainerCard : public Card {
public:
    TrainerCard(string, string);
    void displayInfo();
    string getTrainerEffect();
private:
    string trainerEffect;
};

#endif //POKEMON_TRAINERCARD_H
