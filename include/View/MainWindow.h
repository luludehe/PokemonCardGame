//
// Created by lucas on 13/11/24.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include "../../include/Controller/MainController.h"
//#include "split_screen/split_screen.h"
#include <gtk/gtk.h>

//Déclarations anticipées
class MainController;
class split_screen;

class MainWindow{
public:
    explicit MainWindow(MainController* controller);
    void show();
    GtkWidget* getWindow();
    GtkWidget* window;
    //MainController *controller;
private:
    void initializeWidgets();
    void setupLayout();
    void connectSignals();

    //GtkWidget* window;
    split_screen* splitView;
    MainController* controller;
    GtkWidget* notebook;
};


#endif //MAINWINDOW_H
