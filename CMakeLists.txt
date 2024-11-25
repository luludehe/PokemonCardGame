cmake_minimum_required(VERSION 3.29)
project(PokemonCard)

set(CMAKE_CXX_STANDARD 20)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})

add_executable(PokemonCard main.cpp
        src/Controller/MainController.cpp
        include/Controller/MainController.h
        src/View/MainWindow.cpp
        include/View/MainWindow.h
        src/Model/Card/card.cpp
        src/Model/Card/TrainerCard/trainercard.cpp
        include/Model/Card/TrainerCard/trainercard.h
        src/Model/Card/PokemonCard/pokemoncard.cpp
        include/Model/Card/PokemonCard/pokemoncard.h
        src/Model/Card/Player/player.cpp
        include/Model/Card/Player/player.h
        src/Model/Card/EnergyCard/energycard.cpp
        include/Model/Card/EnergyCard/energycard.h
        src/View/split_screen/split_screen.cpp
        include/View/split_screen/split_screen.h
)

target_link_libraries(PokemonCard ${GTK3_LIBRARIES})