#include <iostream>
#include <gtk/gtk.h>

#include "include/Controller/MainController.h"
#include "include/View/MainWindow.h"

// int main(int argc, char* argv[])
// {
//     gtk_init(&argc, &argv);
//
//     MainController mainController;
//     mainController.run();
//     return 0;
// }

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);  // Initialisation de GTK

    MainController* controller = new MainController();
    if (controller == nullptr) {
        std::cerr << "Error: Failed to initialize controller!" << std::endl;
        return EXIT_FAILURE;
    }
    controller->run();

    //gtk_main();
    return 0;
}
