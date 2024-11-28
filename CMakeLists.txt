cmake_minimum_required(VERSION 3.14)
project(projet_cpp)

# Trouver la bibliothèque PROJ via pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(PROJ REQUIRED proj)

# Options de compilation
set(CMAKE_BUILD_TYPE Debug) # Compilation en mode Debug
set(CMAKE_CXX_STANDARD 17)  # Utiliser le standard C++17
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra") # Options strictes

# Inclure les répertoires d'en-têtes et lier les bibliothèques
include_directories(${PROJ_INCLUDE_DIRS})
link_directories(${PROJ_LIBRARY_DIRS})

# Liste des fichiers source
set(SOURCE_FILES
    src/main.cpp
    src/vibes.cpp
)

# Création de l'exécutable
add_executable(projet_cpp src/main.cpp src/pos.cpp ${SOURCE_FILES})

# Lier l'exécutable avec la bibliothèque PROJ
target_link_libraries(projet_cpp ${PROJ_LIBRARIES})

