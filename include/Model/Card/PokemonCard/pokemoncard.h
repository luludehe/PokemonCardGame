//
// Created by lucas on 15/12/23.
//
#include <string>
#include <vector>
#include "../card.h"
#include "../EnergyCard/energycard.h"

using namespace std;

#ifndef POKEMON_POKEMONCARD_H
#define POKEMON_POKEMONCARD_H

class PokemonCard : public Card {
public:
    PokemonCard(string, string, string, int, int, int, string, int, int, string, int);
    void displayInfo();

    void addEnergyCard(EnergyCard *card);

    string getAttackName(int i);

    int getAttackDamage(int i);

    int hp;

    int getAttackCost(int i);

    int actual_cost;
    int maxHP;

    [[nodiscard]] int getLevel() const { return evolutionLevel; }
    vector< tuple <int, string, int> > getAttacks() { return attacks; }
private:
    string PokemonType;
    string familyName;
    int evolutionLevel;
    vector< tuple <int, string, int> > attacks;
};

#endif //POKEMON_POKEMONCARD_H
