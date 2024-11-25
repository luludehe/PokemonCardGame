//
// Created by lucas on 13/11/24.
//

#include "../../include/View/MainWindow.h"

#include <cassert>
#include <iostream>

#include "../../include/View/split_screen/split_screen.h"
#include <gtk/gtk.h>

#include "../../include/Controller/MainController.h"

MainWindow::MainWindow(MainController* controller)
    : controller(controller) {

    initializeWidgets();
    if (!GTK_IS_WIDGET(window)) {
        std::cerr << "Error: window is not a valid GTK widget!" << std::endl;
        exit(EXIT_FAILURE);
    }
    splitView = controller->getView();
    if (!splitView) {
        std::cerr << "Error: Failed to initialize split_screen!" << std::endl;
        exit(EXIT_FAILURE);
    }
    setupLayout();
}

void MainWindow::setupLayout() {
    splitView->getWidget();
}

GtkWidget* MainWindow::getWindow() {
    return GTK_WIDGET(window);
}

void MainWindow::initializeWidgets() {
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "PokemonCardGame2");
    gtk_window_set_default_size(GTK_WINDOW(window), 1280, 800);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    notebook = gtk_notebook_new();
}

void MainWindow::connectSignals() {
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
}

void MainWindow::show() {
    connectSignals();
    printf(gtk_window_get_title(GTK_WINDOW(window)));
    //gtk_widget_show_all(window);
    splitView->show();
}