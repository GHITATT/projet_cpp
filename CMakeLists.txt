cmake_minimum_required(VERSION 3.14)
project(projet_cpp)

# Trouver la bibliothèque PROJ via pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(PROJ REQUIRED proj)

# Options de compilation
set(CMAKE_BUILD_TYPE Debug)  # Compilation en mode Debug
set(CMAKE_CXX_STANDARD 17)   # Utiliser le standard C++17
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")  # Options strictes

# Inclure les répertoires d'en-têtes pour PROJ
include_directories(${PROJ_INCLUDE_DIRS})

# Si nécessaire, ajouter les répertoires de la bibliothèque
link_directories(${PROJ_LIBRARY_DIRS})

# Si vous utilisez PROJ, assurez-vous que les fichiers de configuration sont copiés correctement
configure_file(${CMAKE_SOURCE_DIR}/src/mnt_brest.txt ${CMAKE_BINARY_DIR}/src/mnt_brest.txt COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/src/mnt_brest_proj.txt ${CMAKE_BINARY_DIR}/src/mnt_brest_proj.txt COPYONLY)

# Liste des fichiers source
set(SOURCE_FILES
    src/main.cpp
    src/vibes.cpp
    src/pos.cpp
    src/triangle.cpp
)

# Création de l'exécutable
add_executable(projet_cpp ${SOURCE_FILES})

# Lier l'exécutable avec la bibliothèque PROJ
target_link_libraries(projet_cpp ${PROJ_LIBRARIES})

# Facultatif : Définir le chemin de recherche de la bibliothèque si nécessaire (par exemple si proj est dans un répertoire non standard)
# link_directories("/path/to/proj/libs")

