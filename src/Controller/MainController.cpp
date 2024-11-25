//
// Created by lucas on 13/11/24.
//

#include "../../include/Controller/MainController.h"
#include "../../include/View/MainWindow.h"
#include "../../include/View/split_screen/split_screen.h"
#include <cassert>
#include <gtk/gtk.h>
#include <iostream>
#include <thread>

MainController* MainController::instance = nullptr;

MainController::MainController() {
    instance = this;
    player = new Player("Sacha");
    enemy = new Player("Team Rocket");

    //mainWindow = new MainWindow(this);
    GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    //GtkWidget* window = mainWindow->window;
    //printf(gtk_window_get_title(GTK_WINDOW(window)));
    assert(window != nullptr && "Failed to create window!");

    view = new split_screen(window, this);
    assert(view != nullptr && "Failed to initialize split_screen!");

    mainWindow = new MainWindow(this);
    assert(mainWindow != nullptr && "Failed to initialize MainWindow!");

    initializeGame();
}

void MainController::run() {
    mainWindow->show();
    gtk_main();
}

void MainController::initializeGame(){
    player->addCardToBench(new EnergyCard("Electric"));
    player->addCardToBench(new EnergyCard("Electric"));
    player->addCardToBench(new PokemonCard("Pikachu", "Electric", "Pikachu", 2, 100, 2, "thunderbolt", 20, 3, "thunderstorm", 30));
    player->activatePokemonCard(2);

    enemy->addCardToBench(new EnergyCard("Electric"));
    enemy->addCardToBench(new EnergyCard("Electric"));
    enemy->addCardToBench(new PokemonCard("Pikachu", "Electric", "Pikachu", 4, 100, 2, "thunderbolt", 20, 3, "thunderstorm", 30));
    enemy->activatePokemonCard(2);

    PokemonCard* player_pokemon = player->getActionCards()[0];
    PokemonCard* enemy_pokemon = enemy->getActionCards()[0];
    view->setPlayerInfoBox(player_pokemon->getCardName().c_str(), player_pokemon->getLevel(),player_pokemon->hp, player_pokemon->maxHP);
    view->setEnemyInfoBox(enemy_pokemon->getCardName().c_str(), enemy_pokemon->getLevel(),enemy_pokemon->hp, enemy_pokemon->maxHP);
}

split_screen* MainController::getView() {
    return view;
}

void MainController::updateEnemyInfo() {

}

void MainController::updateMenuText() {
    std::string newText = "New data";

    g_idle_add([](gpointer data) -> gboolean {
        auto* params = static_cast<std::pair<split_screen*, std::string>*>(data);
        split_screen* view = params->first;
        std::string text = params->second;

        view->setMenuText(text);

        delete params;
        return FALSE;
    }, new std::pair<split_screen*, std::string>(view, newText));
}

void MainController::handleFight() {
    PokemonCard* player_pokemon = player->getActionCards()[0];

    std::vector<std::string> attacks = {"Thunderbolt", "Thunderstorm"};

    g_idle_add([](gpointer data) -> gboolean {
        auto* params = static_cast<std::pair<split_screen*, std::vector<std::string>>*>(data);
        split_screen* view = params->first;
        std::vector<std::string> attacks = params->second;

        view->displayAttacks(attacks);

        delete params;
        return FALSE;
    }, new std::pair<split_screen*, std::vector<std::string>>(view, attacks));
}

void MainController::handleEndTurn() {
    g_idle_add([](gpointer data) -> gboolean {
        auto* view = static_cast<split_screen*>(data);

        view->displayText("It's your opponent's turn!");

        return FALSE;
    }, view);
}

void MainController::handlePokemon(){
    std::string newText = "Pokemon button clicked !";
    player->getName();

    g_idle_add([](gpointer data) -> gboolean {
        auto* params = static_cast<std::pair<split_screen*, std::string>*>(data);
        split_screen* view = params->first;
        std::string text = params->second;

        view->displayText(text);

        delete params;
        return FALSE;
    }, new std::pair<split_screen*, std::string>(view, newText));
}
