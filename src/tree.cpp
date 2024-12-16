#include "tree.h"
#include <iostream>
#include <vector>
#include "node.h"

using namespace std;



Tree::Tree() : _x_min(0), _y_min(0), _x_max(0), _y_max(0), _triangles(0) {}

Tree::Tree(long double x_min, long double y_min, long double x_max, long double y_max, vector<unsigned long> triangles, vector<Pos*> points) : 
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
    int nb_triangles = node->_triangles.size() / 3;
    if (nb_triangles <= min_triangles) {
        return;
    }

    const int MAX_DEPTH = 50;

    if (i > MAX_DEPTH) {
        return;
    }

    box b1, b2;

    if (i % 2 == 0) {

        b1 = {node->_x_min, node->_x_center, node->_y_min, node->_y_max};
        b2 = {node->_x_center, node->_x_max, node->_y_min, node->_y_max};

    } if (i % 2 == 1) {
        // division horizontale
        b1 = {node->_x_min, node->_x_max, node->_y_min, node->_y_center};
        b2 = {node->_x_min, node->_x_max, node->_y_center, node->_y_max};
        
    }

    std::vector<unsigned long> triangles1, triangles2;

    for (size_t k = 0; k < node->_triangles.size(); k += 3) {
        unsigned long t1 = node->_triangles[k];
        unsigned long t2 = node->_triangles[k + 1];
        unsigned long t3 = node->_triangles[k + 2];

        Triangle t(_points[t1], _points[t2], _points[t3]);

        if (triangle_overlaps_box(t, b1)) {
            triangles1.push_back(t1);
            triangles1.push_back(t2);
            triangles1.push_back(t3);
        } else {
            triangles2.push_back(t1);
            triangles2.push_back(t2);
            triangles2.push_back(t3);
        }
    }


    // Création des noeuds seulement si des triangles sont assignés
    if (!triangles1.empty()) {
        Node* Node1 = new Node(b1.xmin, b1.ymin, b1.xmax, b1.ymax, triangles1);
        node->_child1 = Node1;
        subdivide(node->_child1, min_triangles, i + 1);
    }

    if (!triangles2.empty()) {
        Node* Node2 = new Node(b2.xmin, b2.ymin, b2.xmax, b2.ymax, triangles2);
        node->_child2 = Node2;
        subdivide(node->_child2, min_triangles, i + 1);
    }
}


void Tree::search(Node* node, long double x, long double y, vector<unsigned long>& result) {
    if (!node) {
        return;
    }

    // Vérification si les coordonnées sont dans le nœud
    if (!node->in_node(x, y)) {
        return;
    }

    // Si le nœud est une feuille, ajouter ses triangles au résultat
    if (node->is_leaf()) {
        if (!node->_triangles.empty()) {
            result.insert(result.end(), node->_triangles.begin(), node->_triangles.end());
        }
        return;
    }

    // Rechercher dans les sous-nœuds seulement si le nœud n'est pas une feuille
    if (node->_child1) {
        search(node->_child1, x, y, result);
    }
    if (node->_child2) {
        search(node->_child2, x, y, result);
    }
}
