#include "node.h"   
#include <vector>
#include <iostream>

using namespace std;


Node::Node() : _x_min(0), _y_min(0), _x_max(0), _y_max(0), _triangles(0) {}

Node::Node(double x_min, double y_min, double x_max, double y_max, vector<int> triangles) : _x_min(x_min), _y_min(y_min), _x_max(x_max), _y_max(y_max), _triangles(triangles) {
    _x_center = (x_min + x_max) / 2;
    _y_center = (y_min + y_max) / 2;
}

Node::Node(double x_min, double y_min, double x_max, double y_max) : _x_min(x_min), _y_min(y_min), _x_max(x_max), _y_max(y_max), _triangles(0) {
    _x_center = (x_min + x_max) / 2;
    _y_center = (y_min + y_max) / 2;
}

Node::~Node() {
    if (_child1) {
        delete _child1;
    }
    if (_child2) {
        delete _child2;
    }
}

bool Node::is_leaf() {
    return _child1 == nullptr && _child2 == nullptr;
}


bool Node::in_node(double x, double y) {
    return x >= _x_min && x <= _x_max && y >= _y_min && y <= _y_max;
}

