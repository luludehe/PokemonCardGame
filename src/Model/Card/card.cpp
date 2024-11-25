//
// Created by lucas on 15/12/23.
//
#include "../../../include/Model/Card/card.h"
#include <string>
using namespace std;

Card::Card(std::string name) : CardName(name) {}

string Card::getCardName() {
    return CardName;
}