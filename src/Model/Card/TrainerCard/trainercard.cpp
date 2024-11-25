//
// Created by lucas on 18/12/23.
//
#include "../../../../include/Model/Card/card.h"
#include "../../../../include/Model/Card/TrainerCard/trainercard.h"
#include <string>
#include <iostream>
using namespace std;

TrainerCard::TrainerCard(string _TrainerName, string _trainerEffect) :
Card(_TrainerName),
trainerEffect(_trainerEffect)
{
}

void TrainerCard::displayInfo() {
    cout << "\tTrainer Card - Name: " << getCardName() << ", Effect: " << trainerEffect << endl;
}

string TrainerCard::getTrainerEffect() {
    return trainerEffect;
}

