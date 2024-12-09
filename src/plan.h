#ifndef __PLAN_H__
#define __PLAN_H__

#include <iostream>
#include <vector>
#include "pos.h"
#include <limits>

using namespace std;

class Plan
{
    public:

        Plan();
        Plan(vector<Pos*> points);
        ~Plan();


        
        vector<Pos*> _points;
        std::vector<double> coords;  // Définition de coords comme attribut
        std::vector<unsigned long> _triangles;           // Indices des triangles (Delaunator)


        long double _x_min = std::numeric_limits<long double>::max(); 
        long double _y_min = std::numeric_limits<long double>::max(); 
        long double _z_min = std::numeric_limits<long double>::max(); 
        long double _x_max = std::numeric_limits<long double>::lowest();
        long double _y_max = std::numeric_limits<long double>::lowest();
        long double _z_max = std::numeric_limits<long double>::lowest();

        int _width = 1500;
        int _height = 1500;

        int norm_z(long double z);  
        void add_point(const Pos& p) ;
        void generatePGM(const std::string& filename);
        void compute_triangulation();
        double pix_to_m_x(int j);
        double pix_to_m_y(int i);
        bool is_in_triangle(Pos* p1, Pos* p2, Pos* p3, Pos* p);


    private:
        void compute_bounds();

};

#endif // __PLAN_H__