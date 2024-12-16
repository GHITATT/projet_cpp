#include "plan.h"
#include <iostream>
#include <vector>
#include <tbb/parallel_sort.h>
#include "vibes.h"
#include <cmath>
#include <limits>
#include "../external/delaunator-cpp/include/delaunator.hpp"
#include "triangle.h"
#include "node.h"
#include "tree.h"
#include <fstream>

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

long double Plan::pix_to_m_x(int j) {
    return _x_min + ((j * 1.0L) / _width) * (_x_max - _x_min);
}

long double Plan::pix_to_m_y(int i) {
    return _y_min + ((i * 1.0L) / _height) * (_y_max - _y_min);
}



bool Plan::is_in_triangle(Pos* p1, Pos* p2, Pos* p3, Pos* p) {
    Triangle t(p1, p2, p3);
    return t.is_in_circle(p);
}


void Plan::generatePGM(std::string& filename) {
    std::ofstream fout(filename);
    
    if (!fout) {
        std::cerr << "Erreur d’ouverture du fichier " << std::endl;
        return;
    }

    fout << "P2" << std::endl;
    fout << _width << " " << _height << std::endl;
    fout << "255" << std::endl;


    Node root(_x_min, _y_min, _x_max, _y_max, _triangles);
    Tree tree(_x_min, _y_min, _x_max, _y_max, _triangles, _points);


    cout << "Subdivision en cours" << endl;
    tree.subdivide(&root);
    cout << "Subdivision terminée" << endl;

    for (int i = 0; i < _height; i++) {
        for (int j = 0; j < _width; j++) {
            long double x = pix_to_m_x(j);
            
            long double y = pix_to_m_y(i);

            
            vector<unsigned long> result;
            tree.search(&root, x, y, result);
            
            
            if (result.size() > 0) {
                // trouver le triangle le plus proche du point
                vector<unsigned long> dist;
                
                for (std::vector<unsigned long>::size_type k = 0; k < result.size(); k += 3) {
                    unsigned long t1 = result[k];
                    unsigned long t2 = result[k+1];
                    unsigned long t3 = result[k+2];

                    Pos* p1 = _points[t1];
                    Pos* p2 = _points[t2];
                    Pos* p3 = _points[t3];


                    double dp1 = sqrt((p1->_x - x) * (p1->_x - x) + (p1->_y - y) * (p1->_y - y));
                    double dp2 = sqrt((p2->_x - x) * (p2->_x - x) + (p2->_y - y) * (p2->_y - y));
                    double dp3 = sqrt((p3->_x - x) * (p3->_x - x) + (p3->_y - y) * (p3->_y - y));

                    dist.push_back(min(dp1, min(dp2, dp3)));
                    

                
                }
                unsigned long min = dist[0];
                int ti = 0;
                for (std::vector<unsigned long>::size_type k = 1; k < dist.size(); k++) {
                    if (dist[k] < min) {
                        min = dist[k];
                        ti = k;
                    }
                }
                unsigned long t1 = result[ti];
                unsigned long t2 = result[ti+1];
                unsigned long t3 = result[ti+2];

                

                Pos* p1 = _points[t1];
                Pos* p2 = _points[t2];
                Pos* p3 = _points[t3];
                

                int z = norm_z((p1->_z + p2->_z +p3->_z)/3 );
                fout << z << " ";
                //cout << z << " ";

            // } else {
            //     fout << "0 ";
            //     //cout << "0 ";
            // }
            }
            else {
                fout << "0 ";
            }
        }
        fout << std::endl;
    }
    fout.close();


}

void Plan::generatePPM(std::string& filename) {
    std::ofstream fout(filename);
    
    if (!fout) {
        std::cerr << "Erreur d’ouverture du fichier " << std::endl;
        return;
    }

    fout << "P3" << std::endl;
    fout << _width << " " << _height << std::endl;
    fout << "255" << std::endl;


    Node root(_x_min, _y_min, _x_max, _y_max, _triangles);
    Tree tree(_x_min, _y_min, _x_max, _y_max, _triangles, _points);


    cout << "Subdivision en cours" << endl;
    tree.subdivide(&root);
    cout << "Subdivision terminée" << endl;

    for (int i = 0; i < _height; i++) {
        for (int j = 0; j < _width; j++) {
            long double x = pix_to_m_x(j);
            
            long double y = pix_to_m_y(i);

            
            vector<unsigned long> result;
            tree.search(&root, x, y, result);
            
            
            if (result.size() > 0) {
                // trouver le triangle le plus proche du point
                vector<unsigned long> dist;
                
                for (std::vector<unsigned long>::size_type k = 0; k < result.size(); k += 3) {
                    unsigned long t1 = result[k];
                    unsigned long t2 = result[k+1];
                    unsigned long t3 = result[k+2];

                    Pos* p1 = _points[t1];
                    Pos* p2 = _points[t2];
                    Pos* p3 = _points[t3];


                    double dp1 = sqrt((p1->_x - x) * (p1->_x - x) + (p1->_y - y) * (p1->_y - y));
                    double dp2 = sqrt((p2->_x - x) * (p2->_x - x) + (p2->_y - y) * (p2->_y - y));
                    double dp3 = sqrt((p3->_x - x) * (p3->_x - x) + (p3->_y - y) * (p3->_y - y));

                    dist.push_back(min(dp1, min(dp2, dp3)));
                    

                
                }
                unsigned long min = dist[0];
                int ti = 0;
                for (std::vector<unsigned long>::size_type k = 1; k < dist.size(); k++) {
                    if (dist[k] < min) {
                        min = dist[k];
                        ti = k;
                    }
                }
                unsigned long t1 = result[ti];
                unsigned long t2 = result[ti+1];
                unsigned long t3 = result[ti+2];

                

                Pos* p1 = _points[t1];
                Pos* p2 = _points[t2];
                Pos* p3 = _points[t3];
                

                int z = norm_z((p1->_z + p2->_z +p3->_z)/3 );
                int r = z;
                int g = 255 - z;    
                int b = (r+g)/2;
                fout << r << " " << g << " " << b << " ";
                //cout << z << " ";

            // } else {
            //     fout << "0 ";
            //     //cout << "0 ";
            // }
            }
            else {
                fout << "0 0 0 ";
            }
        }
        fout << std::endl;
    }
    fout.close();


}
