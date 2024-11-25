//
// Created by lucas on 13/11/24.
//

#include "../../../include/View/split_screen/split_screen.h"

#include <cassert>
#include <iostream>

#include "../../../include/Controller/MainController.h"

#include <string>
#include <utility>

split_screen::split_screen(GtkWidget* window, MainController* controller)
    : window(window), controller(controller), grid(nullptr), player_view(nullptr), enemy_view(nullptr),
      player_info_box(nullptr), enemy_info_box(nullptr) {

    assert(window != nullptr && "Window is not initialized!");

    if (GTK_IS_WINDOW(window)) {
        gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    } else {
        std::cerr << "Invalid GTK window provided!" << std::endl;
        exit(EXIT_FAILURE);
    }

    printf(gtk_window_get_title(GTK_WINDOW(window)));
    initializeWidgets();
    createActionMenu();
    setupLayout();
    // loadPokemonImage("../assets/pikachu.jpg", player_view, 200, 200);
    // loadPokemonImage("../assets/pikachu.jpg", enemy_view, 200, 200);
    // applyStyles();
    // connectSignals();
    // gtk_widget_show_all(window);
}

void split_screen::initializeWidgets() {
    grid = gtk_grid_new();
    player_view = gtk_image_new();
    enemy_view = gtk_image_new();

    player_info_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    enemy_info_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    player_info_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    enemy_info_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    content_stack = gtk_stack_new();
    gtk_widget_set_name(content_stack, "content-stack");
    text_box = gtk_label_new(boxText.c_str());
    gtk_widget_set_name(text_box, "text-box");
    gtk_stack_add_named(GTK_STACK(content_stack), text_box, "text");

    fight_button = gtk_button_new_with_label("Fight");
    bag_button = gtk_button_new_with_label("Bag");
    pokemon_button = gtk_button_new_with_label("Pokemon");
    run_button = gtk_button_new_with_label("Run");

    gtk_box_pack_start(GTK_BOX(player_info_container), player_info_box, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(enemy_info_container), enemy_info_box, FALSE, FALSE, 0);
    gtk_widget_set_name(player_info_box, "player-info-box");
    gtk_widget_set_name(enemy_info_box, "enemy-info-box");
}

void split_screen::setupLayout() {
    gtk_widget_set_hexpand(grid, TRUE);
    gtk_widget_set_vexpand(grid, TRUE);

    gtk_widget_set_hexpand(player_info_container, TRUE);
    gtk_widget_set_vexpand(player_info_container, TRUE);
    gtk_widget_set_hexpand(player_view, TRUE);
    gtk_widget_set_vexpand(player_view, TRUE);
    gtk_widget_set_hexpand(enemy_info_container, TRUE);
    gtk_widget_set_vexpand(enemy_info_container, TRUE);
    gtk_widget_set_hexpand(enemy_view, TRUE);
    gtk_widget_set_vexpand(enemy_view, TRUE);

    gtk_grid_attach(GTK_GRID(grid), player_info_container, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), player_view, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), enemy_info_container, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), enemy_view, 1, 0, 1, 1);

    gtk_widget_set_size_request(player_view, 400, 300); // Width: 400, Height: 300
    gtk_widget_set_size_request(enemy_view, 400, 300);  // Width: 400, Height: 300
    gtk_widget_set_size_request(player_info_box, -1, 20); // Height: 20px
    gtk_widget_set_size_request(enemy_info_box, -1, 20);  // Height: 20px
    gtk_widget_set_margin_top(player_info_box, 50); // 10px top margin
    gtk_widget_set_margin_top(enemy_info_box, 50);  // 10px top margin

    gtk_container_add(GTK_CONTAINER(window), grid);
}

void split_screen::connectSignals() {
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(fight_button, "clicked", G_CALLBACK(on_fight_clicked), this);
    g_signal_connect(pokemon_button, "clicked", G_CALLBACK(on_pokemon_clicked), this);
}

void split_screen::show() {
    loadPokemonImage("../assets/pikachu.jpg", player_view, 200, 200);
    loadPokemonImage("../assets/pikachu.jpg", enemy_view, 200, 200);
    applyStyles();
    connectSignals();
    gtk_widget_show_all(window);
}

GtkWidget* split_screen::getWidget() {
    assert(grid != nullptr && "grid not initialized!");
    if (!grid) {
        std::cerr << "Error: grid is not initialized!" << std::endl;
        return nullptr;
    }
    return grid;
}

void split_screen::loadPokemonImage(const char* file_path, GtkWidget* target_widget, int width, int height) {
    GError *error = NULL;
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(file_path, &error);
    if (pixbuf) {
        GdkPixbuf *scaled_pixbuf = gdk_pixbuf_scale_simple(pixbuf, width, height, GDK_INTERP_BILINEAR);
        gtk_image_set_from_pixbuf(GTK_IMAGE(target_widget), scaled_pixbuf);
        g_object_unref(pixbuf);
        g_object_unref(scaled_pixbuf);
        gtk_widget_show(target_widget);
    } else {
        g_warning("Failed to load image: %s", error->message);
        g_error_free(error);
    }
}

void split_screen::setInfoBox(GtkWidget* box, const char* name, const int level, const int hp, const int maxHP) {
    GList* children = gtk_container_get_children(GTK_CONTAINER(box));
    for (GList* iter = children; iter != NULL; iter = g_list_next(iter)) {
        gtk_widget_destroy(GTK_WIDGET(iter->data));
    }
    g_list_free(children);

    GtkWidget *name_label = gtk_label_new(name);
    GtkWidget *level_label = gtk_label_new(("Level: " + std::to_string(level)).c_str());
    GtkWidget *hp_label = gtk_label_new(("HP: " + std::to_string(hp)).c_str());
    GtkWidget *hp_bar = gtk_progress_bar_new();
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(hp_bar), hp / (maxHP + 0.0));

    gtk_box_pack_start(GTK_BOX(box), name_label, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), level_label, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), hp_label, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), hp_bar, TRUE, TRUE, 0);
    gtk_widget_show_all(box);
}

void split_screen::setMenuText(const std::string& text) {
    boxText = text;
    gtk_label_set_text(GTK_LABEL(text_box), boxText.c_str());
}

std::string split_screen::getMenuText() {
    return boxText;
}

void split_screen::setEnemyInfoBox(const char* name, int level, int hp, int maxHP) {
    setInfoBox(enemy_info_box, name, level, hp, maxHP);
}

void split_screen::setPlayerInfoBox(const char* name, int level, int hp, int maxHP) {
    setInfoBox(player_info_box, name, level, hp, maxHP);
}

GtkWidget* split_screen::createButtonGrid() {
    GtkWidget* grid = gtk_grid_new();
    const std::vector<std::pair<const char*, GtkWidget**>> buttons = {
        {"Fight", &fight_button},
        {"Bag", &bag_button},
        {"Pokemon", &pokemon_button},
        {"Run", &run_button}
    };

    int i = 0;
    for (const auto& [label, button_ptr] : buttons) {
        *button_ptr = createButton(label, 100, 50);
        gtk_grid_attach(GTK_GRID(grid), *button_ptr, i % 2, i / 2, 1, 1);
        ++i;
    }
    return grid;
}

GtkWidget* split_screen::createButton(const char* label, int width, int height) {
    GtkWidget* button = gtk_button_new_with_label(label);
    gtk_widget_set_size_request(button, width, height);
    return button;
}

void split_screen::createActionMenu() {
    GtkWidget* overlay = gtk_overlay_new();
    grid = gtk_grid_new();
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay), grid);
    action_menu = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

    button_grid = gtk_grid_new();
    gtk_stack_add_named(GTK_STACK(content_stack), button_grid, "attacks");
    gtk_box_pack_start(GTK_BOX(action_menu), content_stack, TRUE, TRUE, 0);

    gtk_widget_set_size_request(fight_button, 100, 50);
    gtk_widget_set_size_request(bag_button, 100, 50);
    gtk_widget_set_size_request(pokemon_button, 100, 50);
    gtk_widget_set_size_request(run_button, 100, 50);

    GtkWidget* right_buttons = gtk_grid_new();
    gtk_grid_attach(GTK_GRID(right_buttons), fight_button, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(right_buttons), bag_button, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(right_buttons), pokemon_button, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(right_buttons), run_button, 1, 1, 1, 1);

    gtk_box_pack_start(GTK_BOX(action_menu), right_buttons, FALSE, FALSE, 0);

    gtk_widget_set_size_request(content_stack, 400, 100);
    gtk_widget_set_size_request(right_buttons, 200, 100);
    gtk_widget_set_valign(action_menu, GTK_ALIGN_END);
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay), action_menu);

    gtk_container_add(GTK_CONTAINER(window), overlay);

    // Ne pas afficher tout pour le moment
}

void split_screen::displayAttacks(const std::vector<std::string>& attacks) {
    if (!button_grid) {
        g_warning("button_grid is not initialized!");
        return;
    }

    GList* children = gtk_container_get_children(GTK_CONTAINER(button_grid));
    for (GList* iter = children; iter != nullptr; iter = iter->next) {
        gtk_widget_destroy(GTK_WIDGET(iter->data));
    }
    g_list_free(children);

    gtk_grid_set_row_homogeneous(GTK_GRID(button_grid), TRUE);
    gtk_grid_set_column_homogeneous(GTK_GRID(button_grid), TRUE);

    int row = 0;
    int col = 0;
    for (const auto& attack : attacks) {
        GtkWidget* button = gtk_button_new_with_label(attack.c_str());

        gtk_widget_set_name(button, "attack-button");

        gtk_grid_attach(GTK_GRID(button_grid), button, col, row, 1, 1);
        col++;
        if (col >= 2) {
            col = 0;
            row++;
        }
    }

    int total_elements = attacks.size();
    for (int i = total_elements; i < 4; i++) {
        GtkWidget* empty_box = gtk_label_new("");
        gtk_grid_attach(GTK_GRID(button_grid), empty_box, col, row, 1, 1);

        col++;
        if (col >= 2) {
            col = 0;
            row++;
        }
    }

    GtkWidget* content_stack = gtk_widget_get_parent(button_grid);
    gtk_stack_set_visible_child_name(GTK_STACK(content_stack), "attacks");

    gtk_widget_show_all(button_grid);
}

void split_screen::displayText(const std::string& text) {
    if (!text_box) {
        g_warning("text_box is not initialized!");
        return;
    }

    boxText = text;
    gtk_label_set_text(GTK_LABEL(text_box), boxText.c_str());

    GtkWidget* content_stack = gtk_widget_get_parent(text_box);
    gtk_stack_set_visible_child_name(GTK_STACK(content_stack), "text");
}

void split_screen::applyStyles() {
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
        "#player-info-box, #enemy-info-box { background-color: ghostwhite; padding: 10px; border: 4px solid gray; }"
        "#player-info-box label, #enemy-info-box label { font-family: 'Pokemon GB'; font-size: 14px; }"
        "#player-view { background-color: lightblue; }"
        "#enemy-view { background-color: lightcoral; }"
        "#player-info-container { background-color: lightgreen; }"
        "#enemy-info-container { background-color: lightyellow; }"
        "#button-grid { background-color: lightgray; border-left: 3px solid black; font-size: 18px}"
        "#action-menu { border: 3px solid black;}"
        "#text-box { background-color: mintcream; font-size: 28px;}"
        "#window { background: linear-gradient(to bottom, #ffcc00, #ff9900); }"
        "#button-grid {padding: 5px; border: 4px solid gray; border-radius: 5px; }"
        "#attack-button { background: linear-gradient(to bottom, #ff4444, #cc0000); border: 2px solid #880000; border-radius: 10px; font-family: 'Verdana', sans-serif; font-size: 16px; font-weight: bold;  color: white; padding: 10px; transition: transform 0.2s, background 0.2s;}"
        "#attack-button:hover { background: linear-gradient(to bottom, #ff6666, #dd2222); transform: scale(1.1); }"
        "#attack-button:active { background: linear-gradient(to bottom, #cc0000, #880000); transform: scale(0.95); }"
        "#action-menu button { background: linear-gradient(to bottom, #00ccff, #0066cc); border: 2px solid #003366; border-radius: 10px; font-family: 'Arial', sans-serif; font-size: 14px; font-weight: bold; color: white; padding: 10px; margin: 5px; transition: transform 0.2s, background 0.2s;}"
        "#action-menu button:hover { background: linear-gradient(to bottom, #33d9ff, #0099ff); transform: scale(1.1); }"
        "#action-menu button:active { background: linear-gradient(to bottom, #0066cc, #003366); transform: scale(0.95); }",
        -1, NULL);

    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                              GTK_STYLE_PROVIDER(provider),
                                              GTK_STYLE_PROVIDER_PRIORITY_USER);

    gtk_widget_set_name(player_info_box, "player-info-box");
    gtk_widget_set_name(enemy_info_box, "enemy-info-box");
    gtk_widget_set_name(player_view, "player-view");
    gtk_widget_set_name(enemy_view, "enemy-view");
    gtk_widget_set_name(player_info_container, "player-info-container");
    gtk_widget_set_name(enemy_info_container, "enemy-info-container");
    gtk_widget_set_name(action_menu, "action-menu");
    gtk_widget_set_name(button_grid, "button-grid");
    gtk_widget_set_name(text_box, "text-box");
    gtk_widget_set_name(window, "window");

    g_object_unref(provider);
}

void split_screen::on_fight_clicked(GtkButton* button, gpointer user_data) {
    split_screen* self = static_cast<split_screen*>(user_data);
    if (self && self->controller) {
        self->controller->handleFight();
    }
}

void split_screen::on_pokemon_clicked(GtkButton* button, gpointer user_data){
    split_screen* self = static_cast<split_screen*>(user_data);
    if (self && self->controller) {
        self->controller->handlePokemon();
    }
}

void split_screen::on_attack_clicked(GtkButton* button, gpointer user_data) {
    split_screen* self = static_cast<split_screen*>(user_data);
    if (self && self->controller) {
        printf("Attatck clicked !");
    }
}

