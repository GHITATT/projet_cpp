#include "plan.h"
#include <iostream>
#include <vector>
#include "pos.h"
#include <tbb/parallel_sort.h>
#include "vibes.h"
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <cmath>



Plan::Plan() : _points(0) {
}

Plan::Plan(vector<Pos*> points) {
    tbb::parallel_sort(points.begin(), points.end(), [](const Pos* a, const Pos* b) {
        return a->_x < b->_x || (a->_x == b->_x && a->_y < b->_y);
    });
    _points = points;
}

Plan::~Plan() {
    for (Pos* p : _points) {
        delete p;
    }
}

void Plan::add_point(const Pos& p) {
    if (std::isnan(p._x) || std::isnan(p._y) || std::isinf(p._x) || std::isinf(p._y)) {
        std::cerr << "Erreur : valeurs invalides pour p._x ou p._y" << std::endl;
        return;
    }
    int i_x = 0;
    int i_y = 0;
    try {
        auto vh = triangulation.insert(Delaunay::Point(p._x, p._y));

        
        const double threshold = 1e-10; // Seuil pour les petites valeurs

        if (p._x < _x_min && p._x > 1) _x_min = p._x;
        if (p._x > _x_max) _x_max = p._x;
        if (p._y < _y_min && p._y > 1) _y_min = p._y;   
        if (p._y > _y_max) _y_max = p._y;   
        if (p._z < _z_min) _z_min = p._z;
        if (p._z > _z_max) _z_max = p._z;

        vh->info() = const_cast<Pos*>(&p); // Utilisez `p._z` si info est un `double`
    } catch (const std::exception& e) {
        std::cerr << "Erreur lors de l'insertion dans la triangulation : " << e.what() << std::endl;
    }
}


void Plan::compute_triangulation() {
    if (_points.empty()) {
        std::cerr << "Erreur : le vecteur de points est vide !" << std::endl;
        return;
    }

    for (size_t i = 0; i < _points.size(); ++i) {
        if (!_points[i]) { 
            std::cerr << "Erreur : pointeur nul trouvé à l'indice " << i << std::endl;
            continue; 
        }
        add_point(*_points[i]);
    }
    cout << "triangulation terminée" << endl;
}

int Plan::norm_z(double z) {
    return round((z - _z_min) / (_z_max - _z_min)*255);
}

void Plan::draw() {

    vibes::beginDrawing();
    vibes::newFigure("Carte MNT");

    std::vector<std::vector<double>> all_x, all_y;

    for (auto face = triangulation.finite_faces_begin(); 
        face != triangulation.finite_faces_end(); ++face) {
        auto p1 = face->vertex(0)->point();
        auto p2 = face->vertex(1)->point();
        auto p3 = face->vertex(2)->point();

        all_x.push_back({p1.x(), p2.x(), p3.x()});
        all_y.push_back({p1.y(), p2.y(), p3.y()});
    }

    // Un seul appel à vibes::drawPolygon
    for (size_t i = 0; i < all_x.size(); ++i) {
        vibes::drawPolygon(all_x[i], all_y[i], "lightGray[blue]");
    }


    vibes::endDrawing();
}

void Plan::generatePGM(const std::string& filename) {
    /*
    const int width = 800;
    const int height = 600;

    // Créer et ouvrir le fichier
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erreur : Impossible de créer le fichier PGM." << std::endl;
        return;
    }

    // Écrire l'en-tête du fichier PGM
    file << "P2\n";                   // Type de fichier (ASCII PGM)
    file << width << " " << height << "\n"; // Dimensions
    file << "255\n"; 
    */
    cout << "xmax = " << _x_max<< " ymax = " << _y_max  << " xmin = " << _x_min << " ymin= " << _y_min << endl;
    
}