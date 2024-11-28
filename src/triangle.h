#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include <iostream>
#include "pos.h"


class Triangle
{
public:
    Triangle();

    Triangle(Pos* p1, Pos* p2, Pos* p3);

    ~Triangle();

    Pos* _p1;
    Pos* _p2;
    Pos* _p3;

    void calculer_coefficients(); // calculer les coefficients des 2 droites mediatrices des segment (p1, p2) et (p2, p3)   

    void calculer_center(); // calculer le centre du cercle circonscrit au triangle

    void calculer_rayon(); // calculer le rayon du cercle circonscrit au triangle
    
    bool is_in_circle(Pos* p); // vérifier si un point est dans le cercle circonscrit au triangle

    double _a1, _a2, _b1, _b2, _c1, _c2;
    double _x, _y; 
    double _r;
};




#endif // __TRIANGLE_H__