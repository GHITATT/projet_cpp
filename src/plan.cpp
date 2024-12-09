#include "plan.h"
#include <iostream>
#include <vector>
#include <tbb/parallel_sort.h>
#include "vibes.h"
#include <cmath>
#include <limits>
#include "../external/delaunator-cpp/include/delaunator.hpp"
#include "triangle.h"

using namespace std;

Plan::Plan() :  
    _points(0)
{}

Plan::Plan(vector<Pos*> points) : _points(points) {
    // Trier les points par coordonnée X, puis par Y
    tbb::parallel_sort(_points.begin(), _points.end(), [](const Pos* a, const Pos* b) {
        return a->_x < b->_x || (a->_x == b->_x && a->_y < b->_y);
    });

    // Calculer les limites (x_min, y_min, z_min, ...)
    compute_bounds();

    compute_triangulation();    
}

Plan::~Plan() {
    for (Pos* p : _points) {
        delete p;
    }
}

void Plan::compute_triangulation(){
    coords.reserve(_points.size() * 2);
    for (const auto& p : _points) {
        if (p) {
            coords.push_back(static_cast<double>(p->_x));
            coords.push_back(static_cast<double>(p->_y));
        }
    }

    try {
        // Effectuer la triangulation
        delaunator::Delaunator d(coords);

        // Stocker les indices des triangles
        _triangles = d.triangles;

    } catch (const std::exception& e) {
        cerr << "Erreur lors de la triangulation avec Delaunator : " << e.what() << endl;
    }
}


// Méthode pour calculer les limites (_x_min, _y_min, ...)
void Plan::compute_bounds() {

    for (const auto& p : _points) {
        if (p) {
            _x_min = std::min(_x_min, p->_x);
            _x_max = std::max(_x_max, p->_x);
            _y_min = std::min(_y_min, p->_y);
            _y_max = std::max(_y_max, p->_y);
            _z_min = std::min(_z_min, p->_z);
            _z_max = std::max(_z_max, p->_z);
        }
    }
}

int Plan::norm_z(long double z) {
    return static_cast<int>((z - _z_min) / (_z_max - _z_min) * 255);
}

double Plan::pix_to_m_x(int j) {
    return _x_min + (j/_width) * (_x_max - _x_min);
}

double Plan::pix_to_m_y(int i) {
    return _y_min + (i/_height) * (_y_max - _y_min);
}

bool Plan::is_in_triangle(Pos* p1, Pos* p2, Pos* p3, Pos* p) {
    Triangle t(p1, p2, p3);
    return t.is_in_circle(p);
}


void Plan::generatePGM(const std::string& filename) {
    cout << "xmax = " << _x_max << " ymax = " << _y_max
         << " xmin = " << _x_min << " ymin = " << _y_min << endl;
    cout << "width = " << _x_max - _x_min << " height = " << _y_max - _y_min << endl;
}
