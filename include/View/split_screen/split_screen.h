//
// Created by lucas on 13/11/24.
//

#ifndef SPLIT_SCREEN_H
#define SPLIT_SCREEN_H

#include <string>
#include <gtk/gtk.h>
//#include "../../Controller/MainController.h"
#include "../../Model/Card/PokemonCard/pokemoncard.h"

//Déclarations anticipées
class MainController;

class split_screen {
public:
    split_screen(GtkWidget* window, MainController* controller);
    void show();
    GtkWidget* getWidget();
    void loadPokemonImage(const char* file_path, GtkWidget* target_widget, int width = 200, int height = 200);
    void setMenuText(const std::string& text);
    std::string getMenuText();
    void setEnemyInfoBox(const char* name, int level, int hp, int maxHP);
    void setPlayerInfoBox(const char* name, int level, int hp, int maxHP);
    void setAttackButtons(PokemonCard* pokemon) const;
    void displayAttacks(const std::vector<std::string>& attacks);
    void displayText(const std::string& text);
private:
    void initializeWidgets();
    void setupLayout();
    void connectSignals();
    void applyStyles();
    void createActionMenu();
    GtkWidget* createButton(const char* label, int width, int height);
    GtkWidget* createButtonGrid();
    static void on_attack_clicked(GtkButton* button, gpointer user_data);
    void setInfoBox(GtkWidget* box, const char* name, int level, int hp, int maxHP);
    static void on_fight_clicked(GtkButton* button, gpointer user_data);
    static void on_pokemon_clicked(GtkButton* button, gpointer user_data);

    GtkWidget *window;
    MainController *controller;
    GtkWidget *grid;
    GtkWidget *player_view;
    GtkWidget *enemy_view;
    GtkWidget *player_info_box;
    GtkWidget *enemy_info_box;
    GtkWidget *player_info_container;
    GtkWidget *enemy_info_container;
    GtkWidget* overlay;
    GtkWidget* content_stack;
    GtkWidget *action_menu;
    GtkWidget *button_grid;
    GtkWidget *text_box;
    std::string boxText = "Hello World!";
    GtkWidget *fight_button;
    GtkWidget *bag_button;
    GtkWidget *pokemon_button;
    GtkWidget *run_button;

};

#endif //SPLIT_SCREEN_H
