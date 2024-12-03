#include "triangle.h"
#include <iostream>
#include <cmath>

using namespace std;

Triangle::Triangle() : _p1(nullptr), _p2(nullptr), _p3(nullptr), _a1(0), _a2(0), _b1(0), _b2(0), _c1(0), _c2(0), _x(0), _y(0) {
    /*
    _p1->link_to(_p2);
    _p2->link_to(_p3);
    */
    

}

Triangle::Triangle(Pos* p1, Pos* p2, Pos* p3) : _p1(p1), _p2(p2), _p3(p3){
    calculer_coefficients();
    calculer_center();
    /*
    _p1->link_to(_p2);
    _p2->link_to(_p3);
    */
}

Triangle::~Triangle() {
}


void Triangle::calculer_coefficients(){
    //segment (p1, p2)
    _a1 = 2 * (_p2->_x - _p1->_x);
    _b1 = 2 * (_p2->_y - _p1->_y);
    _c1 = _p1->_x * _p1->_x + _p1->_y * _p1->_y - _p2->_x * _p2->_x - _p2->_y * _p2->_y;

    //segment (p2, p3)
    _a2 = 2 * (_p3->_x - _p2->_x);  
    _b2 = 2 * (_p3->_y - _p2->_y);  
    _c2 = _p2->_x * _p2->_x + _p2->_y * _p2->_y - _p3->_x * _p3->_x - _p3->_y * _p3->_y;

}

void Triangle::calculer_center(){
    double det = _a1 * _b2 - _a2 * _b1;
    if (det == 0){
        cout << "Erreur : les droites mediatrices ne se croisent pas" << endl;
        return;
    }
    _x = - (_c1 * _b2 - _c2 * _b1) / det;
    _y = - (_a1 * _c2 - _a2 * _c1) / det;
}

void Triangle::calculer_rayon(){
    double _r_carre = (_x - _p1->_x) * (_x - _p1->_x) + (_y - _p1->_y) * (_y - _p1->_y);
    _r = sqrt(_r_carre);
}

bool Triangle::is_in_circle(Pos* p){
    double d = sqrt((p->_x - _x) * (p->_x - _x) + (p->_y - _y) * (p->_y - _y));
    if (d < _r){
        return true;
    }
    else{
        return false;
    }
}