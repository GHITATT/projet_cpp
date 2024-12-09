#include <proj.h>
#include <iostream>
#include <fstream>
#include "pos.h"
#include <vector>
#include "triangle.h"
#include "plan.h"
#include "proj_class.cpp"

using namespace std;

std::string mnt_brest = "src/mnt_brest.txt";
std::string mnt_brest_pgm = "src/mnt_brest.pgm";
vector<Pos*> points;

int read_mnt(std::string& mnt_brest) {
    std::ifstream fin(mnt_brest);

    if (!fin.is_open()) {
        cout << "Erreur d’ouverture de " << mnt_brest << endl;
        return 1;
    }

    std::string line;
    size_t line_count = 0;

    // Lire chaque ligne du fichier
    while (std::getline(fin, line)) {
        std::istringstream iss(line);
        long double lat, lon, alt;

        if (!(iss >> lat >> lon >> alt)) {
            std::cerr << "Erreur de lecture à la ligne " << line_count << std::endl;
            return 1;
        }

        Pos* p = new Pos(lat, lon, alt);

        points.push_back(p);

        ++line_count;
        /*
        // Limite de test (supprimez cette ligne pour traiter tout le fichier)
        if (line_count >= 1000) {
            break;
        }
        */
        
    
        
        
    }

    cout << "Lecture terminée : " << line_count << " points lus." << endl;

    fin.close();
    return 0;
}

int main() {
    // Initialisation unique de PROJ
    try {
        Proj::initialize();
    } catch (const std::exception& e) {
        std::cerr << "Erreur lors de l'initialisation de PROJ : " << e.what() << std::endl;
        return 1;
    }

    // Lire les points MNT
    bool read = read_mnt(mnt_brest);
    if (read == 1) {
        Proj::cleanup(); // Nettoyage avant de quitter
        return 1;
    }

    // Créer et utiliser l'objet Plan
    Plan plan(points);
    plan.compute_triangulation();
    //plan.draw();
    plan.generatePGM("mnt_brest.pgm");

    // Nettoyage final de PROJ
    Proj::cleanup();
    return 0;
}
