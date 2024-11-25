//
// Created by lucas on 18/12/23.
//
#include <string>
#include <vector>
#include "../card.h"
#include "../PokemonCard/pokemoncard.h"
using namespace std;

class Player {
public:
    explicit Player(string);
    void displayInfo();

    void addCardToBench(Card* card);
    void displayBench();

    void activatePokemonCard(int i);
    void attachEnergyCard(int i, int i1);

    void displayAction();

    void attack(int use_pokemon, int use_attack, Player player, int player_pokemon);

    void useTrainer(int i);

    string getName(){ return playerName;}
    vector<Card*> getBenchCards(){ return benchCards;}
    vector<PokemonCard*> getActionCards(){ return actionCards;}

private:
    string playerName;
    vector<Card*> benchCards;
    vector<PokemonCard*> actionCards;
};

#ifndef POKEMON_PLAYER_H
#define POKEMON_PLAYER_H

#endif //POKEMON_PLAYER_H
