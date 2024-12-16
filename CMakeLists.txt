cmake_minimum_required(VERSION 3.14)
project(projet_cpp)

# Activer les options de compilation strictes et utiliser C++17
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# Trouver PROJ via pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(PROJ REQUIRED proj)

# Inclure PROJ
include_directories(${PROJ_INCLUDE_DIRS})
link_directories(${PROJ_LIBRARY_DIRS})

# Trouver et inclure TBB
find_package(TBB REQUIRED)

# Copier les fichiers de données nécessaires
configure_file(${CMAKE_SOURCE_DIR}/src/mnt_brest.txt ${CMAKE_BINARY_DIR}/src/mnt_brest.txt COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/src/mnt_brest.pgm ${CMAKE_BINARY_DIR}/src/mnt_brest.pgm COPYONLY)

set(DELAUNATOR_SOURCES external/delaunator-cpp/include/delaunator.hpp)

# Liste des fichiers source
set(SOURCE_FILES
    src/main.cpp
    src/pos.cpp
    src/plan.cpp
    src/vibes.cpp
    src/proj_class.cpp
    src/tree.cpp
    src/node.cpp
    src/triangle.cpp
)

# Création de l'exécutable
add_executable(projet_cpp ${SOURCE_FILES} ${DELAUNATOR_SOURCES})

# Lier l'exécutable avec les bibliothèques nécessaires
target_link_libraries(projet_cpp ${PROJ_LIBRARIES} TBB::tbb)

