#ifndef __TREE_H__
#define __TREE_H__

#include <iostream>
#include <vector>
#include "node.h"
#include "pos.h"
#include "triangle.h"

using namespace std;

struct box {
    double xmin, xmax, ymin, ymax;

    bool overlaps(const box& b) {
        return xmin <= b.xmax && xmax >= b.xmin && ymin <= b.ymax && ymax >= b.ymin;
    }

    bool contains(double x, double y) {
        return x >= xmin && x <= xmax && y >= ymin && y <= ymax;
    }
};

class Tree
{
public:
    Tree();
    Tree(double x_min, double y_min, double x_max, double y_max, vector<int> triangles, vector<Pos*> points);
    ~Tree();

    Node* _root = nullptr;
    double _x_min, _y_min, _x_max, _y_max;
    vector<int> _triangles;
    vector<Pos*> _points;
    double _x_center, _y_center;


    bool triangle_overlaps_box(Triangle t, box b);
    void subdivide(Node* node, int min_triangles = 5, int i = 0);
    void search(Node* node, double x, double y, vector<int>& result);
};

#endif // __TREE_H__    