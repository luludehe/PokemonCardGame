//
// Created by lucas on 13/11/24.
//

#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

//#include "../View/MainWindow.h"
//#include "../View/split_screen/split_screen.h"
#include "../../include/Model/Card/Player/player.h"
#include <string>
#include <gtk/gtk.h>

//Déclarations anticipées
class MainWindow;
class split_screen;

class MainController {
public:
    MainController();
    void run();

    std::string getDataForDisplay();
    void updateEnemyInfo();
    void handleFight();
    void handlePokemon();
    void updateMenuText();
    split_screen* getView();
private:
    void initializeGame();
    void handleEndTurn();
    MainWindow* mainWindow;
    split_screen* view;
    static MainController* instance;
    //mainModel model;
    Player* player;
    Player* enemy;
};

#endif //MAINCONTROLLER_H
