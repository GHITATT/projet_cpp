#ifndef __PLAN_H__
#define __PLAN_H__

#include <iostream>
#include <vector>
#include "pos.h"
#include <limits>
#include <fstream>

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

        int _width = 2000;
        int _height = 2000;

        int norm_z(long double z);  
        void add_point(const Pos& p) ;
        void generatePGM(std::string& filename);
        void generatePPM(std::string& filename);
        void compute_triangulation();
        long double pix_to_m_x(int j);
        long double pix_to_m_y(int i);
        bool is_in_triangle(Pos* p1, Pos* p2, Pos* p3, Pos* p);
        void haxby_colormap(int z, int& r, int& g, int& b);

    private:
        void compute_bounds();

};

#endif // __PLAN_H__