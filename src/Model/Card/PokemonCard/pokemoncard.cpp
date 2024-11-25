//
// Created by lucas on 15/12/23.
//
#include "../../../../include/Model/Card/PokemonCard/pokemoncard.h"
#include "../../../../include/Model/Card/card.h"
#include <string>
#include <iostream>
using namespace std;

PokemonCard::PokemonCard(string _CardName, string _PokemonType, string _familyName, int _evolutionLevel, int _maxHP, int cost_1, string attack_name_1, int damage_1, int cost_2, string attack_name_2, int damage_2) :
Card(_CardName),
PokemonType(_PokemonType),
familyName(_familyName),
evolutionLevel(_evolutionLevel),
maxHP(_maxHP),
hp(_maxHP),
actual_cost(0) {
    cout << damage_1 << endl;
    attacks.push_back(make_tuple(cost_1, attack_name_1, damage_1));
    attacks.push_back(make_tuple(cost_2, attack_name_2, damage_2));
}

void PokemonCard::displayInfo() {
    cout << "\tPokemon Card: " << endl;
    cout << "\t\tPokemon Type: " << PokemonType << endl;
    cout << "\t\tFamily Name: " << familyName << endl;
    cout << "\t\tEvolution Level: " << evolutionLevel << endl;
    cout << "\t\tMax HP: " << maxHP << endl;
    cout << "\t\tHP: " << hp << endl;
    cout << "\t\tAttacks: " << endl;
    for (int i = 0; i < attacks.size(); i++) {
        cout << "\t\t\tAttack #" << i+1 << ": " << endl;
        cout << "\t\t\t\tAttack Cost: " << get<0>(attacks[i]) << endl;
        cout << "\t\t\t\tAttack current energy storage: " << actual_cost << endl;
        cout << "\t\t\t\tAttack description: " << get<1>(attacks[i]) << endl;
        cout << "\t\t\t\tAttack damage: " << get<2>(attacks[i]) << endl;
    }
}

void PokemonCard::addEnergyCard(EnergyCard *card) {
    actual_cost += 1;
}

string PokemonCard::getAttackName(int i) {
    return get<1>(attacks[i]);
}

int PokemonCard::getAttackDamage(int i){
    return get<2>(attacks[i]);
}

int PokemonCard::getAttackCost(int i) {
    return get<0>(attacks[i]);
}