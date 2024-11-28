#include <proj.h>
#include <iostream>
#include <fstream>
#include "pos.h"
#include <vector>
#include "triangle.h"

using namespace std;

std::string mnt_brest = "src/mnt_brest.txt";
vector <Pos*> points;



int read_mnt(std::string& mnt_brest) {
    std::ifstream fin(mnt_brest);

    if (!fin.is_open()){
        cout << "Erreur d’ouverture de " << mnt_brest << endl;
        return 1;
    }


    else{
        for (int i = 0; i < 500; i++){
            Pos* p = new Pos();
            fin >> *p;
            points.push_back(p);
            delete p;
        }
    }
    cout << "premier proj " << points[0]->_x << points[0]->_y << endl;
    fin.close();
    return 0;
}


Triangle super_triangle(vector <Pos*> points){

    Pos p1;
    Pos p2;
    Pos p3;

    double xmin = points[0]->_x;
    double xmax = points[0]->_x;
    double ymin = points[0]->_y;
    double ymax = points[0]->_y;

    // Recherche des limites du rectangle englobant
    for (const auto& p : points){
        if (p->_x < xmin){
            xmin = p->_x;
        }
        if (p->_x > xmax){
            xmax = p->_x;
        }
        if (p->_y < ymin){
            ymin = p->_y;
        }
        if (p->_y > ymax){
            ymax = p->_y;
        }
    }
    cout << xmin << " " << xmax << " " << ymin << " " << ymax << endl;

    // largeur et hauteur du rectangle

    double width = xmax - xmin;
    double height = ymax - ymin;

    // Marge 
    double delta = 10 * max(width, height);

    p1._x = xmin - delta;
    p1._y = ymin - delta;
    p1._x = xmax + delta;
    p2._y = ymin - delta;
    p3._x = (xmin + xmax) / 2;
    p3._y = ymax + delta;

    return Triangle(&p1, &p2, &p3);
}


int main() {
    bool read = read_mnt(mnt_brest);
    if (read == 1){
        return 1;
    }
    super_triangle(points);
    return 0;
}
