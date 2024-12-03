#ifndef __PLAN_H__
#define __PLAN_H__

#include <iostream>
#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_data_structure_2.h>
#include "pos.h"

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<Pos*, K> Vb;
typedef CGAL::Triangulation_data_structure_2<Vb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Delaunay;


class Plan
{
public:
    Delaunay triangulation; 

    Plan();
    Plan(vector<Pos*> points);
    ~Plan();


    
    vector<Pos*> _points;
    double _x_min, _x_max, _y_min, _y_max, _z_min, _z_max;

    int norm_z(double z);  
    void add_point(const Pos& p) ;
    void generatePGM(const std::string& filename);
    void compute_triangulation();
    void draw();

};

#endif // __PLAN_H__