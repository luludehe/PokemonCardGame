//
// Created by lucas on 18/12/23.
//
#include "../../../../include/Model/Card/Player/player.h"
#include "../../../../include/Model/Card/card.h"
#include "../../../../include/Model/Card/TrainerCard/trainercard.h"
#include <string>
#include <iostream>

using namespace std;
Player::Player(string _playerName) :
playerName(_playerName)
{
}

void Player::addCardToBench(Card* card) {
    benchCards.push_back(card);
}

void Player::displayBench() {
    cout << "Bench Cards for " << playerName << " :"<< endl;
    for (int i = 0; i < benchCards.size(); i++) {
        benchCards[i]->displayInfo();
    }
}

void Player::activatePokemonCard(int i) {
    PokemonCard* tmp = dynamic_cast<PokemonCard*>(benchCards[i]);
    if (benchCards[i] == NULL) {
        cout << "Error: Invalid card index" << endl;
    }
    else if (tmp == nullptr) {
        cout << "Error: Invalid card type" << endl;
    }
    else
    {
        cout << playerName << " is activating a Pokemon Card: " << benchCards[i]->getCardName() << endl;
        actionCards.push_back(tmp);

        benchCards.erase(benchCards.begin() + i);
        //delete benchCards[i];
        cout << actionCards[0]->getCardName() << endl;
    }
}

void Player::attachEnergyCard(int i, int i1) {
    EnergyCard* energy = dynamic_cast<EnergyCard*>(benchCards[i]);
    PokemonCard* pokemon = dynamic_cast<PokemonCard*>(actionCards[i1]);
    if (benchCards.size() < i || actionCards.size() < i1) {
        cout << "Error: Invalid card index" << endl;
    }
    else if (energy == nullptr || pokemon == nullptr) {
        cout << "Error: Invalid card type" << endl;
    }
    else {
        cout << playerName << " is attaching Energy Card of type " << energy->getEnergyType() << " to the Pokemon" << endl;
        actionCards[i1]->addEnergyCard(energy);
        delete benchCards[i];
        benchCards.erase(benchCards.begin() + i);
    }
}

void Player::displayAction() {
    cout << "Action Cards for " << playerName << " :" << endl;
    for (int i = 0; i < actionCards.size(); i++) {
        actionCards[i]->displayInfo();
    }
}

void Player::displayInfo() {
    cout << "Player Name: " << playerName << endl;
    displayBench();
    displayAction();
}

void Player::useTrainer(int i) {
    TrainerCard* trainer = dynamic_cast<TrainerCard*>(benchCards[i]);
    cout << "Player " << playerName << " is using Trainer Card to \""<< trainer->getTrainerEffect() << "\""<< endl;
    for (int j = 0; j < actionCards.size(); j++) {
        actionCards[j]->hp = actionCards[j]->maxHP;
    }
}

void Player::attack(int i, int i1, Player player, int i2) {
    if (actionCards.size() < i1 || player.actionCards.size() < i2) {
        cout << "Error: Invalid card index" << endl;
    }
    if (actionCards[i]->actual_cost < actionCards[i]->getAttackCost(i1)) {
        cout << "Error: Not enough energy to use this attack" << endl;
    } else {
        cout << "Player " << playerName << " is attacking " << player.playerName << "'s "
             << player.actionCards[i2]->getCardName() << " with its attack: " << actionCards[i]->getAttackName(i2)
             << endl;
        cout << "Reducing " << actionCards[i]->getAttackDamage(i1) << "HP from " << player.playerName
             << "'s Pokemon's HP" << endl;
        player.actionCards[i2]->hp -= actionCards[i]->getAttackDamage(i1);
        if (player.actionCards[i2]->hp <= 0) {
            cout << "Pokemon " << player.actionCards[i2]->getCardName() << " is dead" << endl;
            player.actionCards.erase(player.actionCards.begin() + i2);
        } else {
            cout << "Pokemon " << player.actionCards[i2]->getCardName() << " is still alive ("
                 << player.actionCards[i2]->hp << "HP left)" << endl;
        }
        actionCards[i]->actual_cost -= actionCards[i]->getAttackCost(i1);
    }
}