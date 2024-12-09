#include "tree.h"
#include <iostream>
#include <vector>
#include "node.h"

using namespace std;



Tree::Tree() : _x_min(0), _y_min(0), _x_max(0), _y_max(0), _triangles(0) {}

Tree::Tree(double x_min, double y_min, double x_max, double y_max, vector<int> triangles, vector<Pos*> points) : 
            _x_min(x_min), _y_min(y_min), 
            _x_max(x_max), _y_max(y_max), 
            _triangles(triangles),
            _points(points) {

    _root = new Node(x_min, y_min, x_max, y_max, triangles);
    _x_center = (x_min + x_max) / 2;
    _y_center = (y_min + y_max) / 2;
}

Tree::~Tree() {
    if (_root) {
        delete _root;
    }
}

bool Tree::triangle_overlaps_box(Triangle t, box b) {
    box tb ;
    tb.xmin = min(t._p1->_x, min(t._p2->_x, t._p3->_x));
    tb.xmax = max(t._p1->_x, max(t._p2->_x, t._p3->_x));
    tb.ymin = min(t._p1->_y, min(t._p2->_y, t._p3->_y));
    tb.ymax = max(t._p1->_y, max(t._p2->_y, t._p3->_y));

    return tb.overlaps(b);
}



void Tree::subdivide(Node* node, int min_triangles, int i) {
    int nb_triangles = node->_triangles.size()/3;
    if (nb_triangles <= min_triangles) {
        return;
    }

    double xmin1 = 0.0, xmax1 = 0.0, ymin1 = 0.0, ymax1 = 0.0;
    double xmin2 = 0.0, xmax2 = 0.0, ymin2 = 0.0, ymax2 = 0.0;
    box b1, b2;

    if (i % 2 == 0) {
        // division verticale
        xmin1 = node->_x_min;
        xmax1 = node->_x_center;

        ymin1 = node->_y_min;
        ymax1 = node->_y_max;

        xmin2 = node->_x_center;
        xmax2 = node->_x_max;

        b1 = {xmin1, xmax1, ymin1, ymax1};
        b2 = {xmin2, xmax2, ymin1, ymax1};

    } else {
        // division horizontale
        ymin1 = node->_y_min;
        ymax1 = node->_y_center;

        xmin2 = node->_x_min;
        xmax2 = node->_x_max;

        ymin2 = node->_y_center;
        ymax2 = node->_y_max;

        b1 = {xmin2, xmax1, ymin1, ymax1};
        b2 = {xmin1, xmax2, ymin2, ymax2};
    }
    
    vector<int> triangles1, triangles2;

    for (int i = 0; i < nb_triangles; i+=3) {
        int t1 = node->_triangles[i];
        int t2 = node->_triangles[i+1];
        int t3 = node->_triangles[i+2];

        Triangle t(_points[t1], _points[t2], _points[t3]);

        if (triangle_overlaps_box(t, b1)) {
            triangles1.push_back(t1);
            triangles1.push_back(t2);
            triangles1.push_back(t3);
        }

        if (triangle_overlaps_box(t, b2)) {
            triangles2.push_back(t1);
            triangles2.push_back(t2);
            triangles2.push_back(t3);
        }
    }

    node->_child1 = new Node(b1.xmin, b1.ymin, b1.xmax, b1.ymax, triangles1);
    node->_child2 = new Node(b2.xmin, b2.ymin, b2.xmax, b2.ymax, triangles2);

    subdivide(node->_child1, min_triangles, i+1);
    subdivide(node->_child2, min_triangles, i+1);    
}

void Tree::search(Node* node, double x, double y, vector<int>& result) {
    if (!node) {
        return ;
    }

    if (!node->in_node(x, y)) {
        return ;
    }

    if (node->is_leaf()) {
        result.insert(result.end(), node->_triangles.begin(), node->_triangles.end());
        return ;
    }

    search(node->_child1, x, y, result);
    search(node->_child2, x, y, result);
}