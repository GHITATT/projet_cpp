#ifndef __NODE_H__
#define __NODE_H__

#include <iostream>
#include <vector>


using namespace std;

class Node
{

public:
    Node();
    Node(double x_min, double y_min, double x_max, double y_max, vector<int> triangles);
    Node(double x_min, double y_min, double x_max, double y_max);
    ~Node();

    Node* _child1 = nullptr;
    Node* _child2 = nullptr;

    double _x_min, _y_min, _x_max, _y_max;
    vector<int> _triangles;

    double _x_center, _y_center;

    bool is_leaf();
    bool in_node(double x, double y);
};

#endif // __NODE_H__    

