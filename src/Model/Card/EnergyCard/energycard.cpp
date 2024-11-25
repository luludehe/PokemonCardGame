//
// Created by lucas on 18/12/23.
//
#include "../../../../include/Model/Card/EnergyCard/energycard.h"
#include "../../../../include/Model/Card/card.h"
#include <string>
#include <iostream>
using namespace std;

EnergyCard::EnergyCard(string _energyType) :
Card("Energy"),
energyType(_energyType){
}

void EnergyCard::displayInfo() {
    cout << "\tEnergy Card - Energy Type: " << energyType << endl;
}

string EnergyCard::getEnergyType() {
    return energyType;
}
