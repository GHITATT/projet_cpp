#include "plan.h"
#include <iostream>
#include <vector>
#include "pos.h"
#include <tbb/parallel_sort.h>
#include "vibes.h"
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <cmath>
#include <limits>


using namespace std;


Plan::Plan() :  
    _points(0),
    _x_min(std::numeric_limits<long double>::max()), 
    _y_min(std::numeric_limits<long double>::max()), 
    _z_min(std::numeric_limits<long double>::max()), 
    _x_max(std::numeric_limits<long double>::lowest()), 
    _y_max(std::numeric_limits<long double>::lowest()), 
    _z_max(std::numeric_limits<long double>::lowest()) 
{}


Plan::Plan(vector<Pos*> points) {
    tbb::parallel_sort(points.begin(), points.end(), [](const Pos* a, const Pos* b) {
        return a->_x < b->_x || (a->_x == b->_x && a->_y < b->_y);
    });
    _points = points;

    _x_min = std::numeric_limits<long double>::max();
    _y_min = std::numeric_limits<long double>::max(); 
    _z_min = std::numeric_limits<long double>::max();
    _x_max = std::numeric_limits<long double>::lowest(); 
    _y_max = std::numeric_limits<long double>::lowest(); 
    _z_max = std::numeric_limits<long double>::lowest();
}

Plan::~Plan() {
    for (Pos* p : _points) {
        delete p;
    }
}

void Plan::add_point(const Pos& p) {
    if (std::isnan(p._x) || std::isnan(p._y) || std::isnan(p._z) || 
    std::isinf(p._x) || std::isinf(p._y) || std::isinf(p._z)) {
    std::cerr << "Erreur : valeurs invalides pour p._x, p._y ou p._z" << std::endl;
    return;
}
    _x_min = std::min(_x_min, p._x);
    _x_max = std::max(_x_max, p._x);
    _y_min = std::min(_y_min, p._y);
    _y_max = std::max(_y_max, p._y);
    _z_min = std::min(_z_min, p._z);
    _z_max = std::max(_z_max, p._z);

    try {
        auto vh = triangulation.insert(Delaunay::Point(p._x, p._y));

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

    // Utilisation de valeurs minimales et maximales prédéfinies

    cout << "triangulation terminée" << endl;
}

// int Plan::norm_z(long double z) {
//     return round((z - _z_min) / (_z_max - _z_min)*255);
// }

void Plan::draw() {
    if (triangulation.number_of_faces() == 0) {
        std::cerr << "Erreur : la triangulation est vide !" << std::endl;
        return;
    }

    vibes::beginDrawing();
    vibes::newFigure("Carte MNT");

    std::vector<std::vector<long double>> all_x, all_y;

    for (auto face = triangulation.finite_faces_begin(); face != triangulation.finite_faces_end(); ++face) {
        auto p1 = face->vertex(0)->point();
        auto p2 = face->vertex(1)->point();
        auto p3 = face->vertex(2)->point();

        all_x.push_back({p1.x(), p2.x(), p3.x()});
        all_y.push_back({p1.y(), p2.y(), p3.y()});
    }

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
    cout << "width = " << _x_max - _x_min << " height = " << _y_max - _y_min << endl;

}