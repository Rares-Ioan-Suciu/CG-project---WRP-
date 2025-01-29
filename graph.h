//
// Created by rares655 on 12/31/24.
//

#ifndef GRAPH_H
#define GRAPH_H


#include <CGAL/Simple_cartesian.h>
#include <set>
#include <tuple>

typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_2 Point;

// this file is simply used to create a data structe for the graph, also creating the edge data strcutre in order to ease computaion in
// the dijsktra's algorithm and A*. We implement the
struct Edge {
    Point u;
    Point v;
    double weight;

    Edge(const Point& a, const Point& b, double w) : u(a), v(b), weight(w) {
        if (CGAL::compare_xy(u, v) == CGAL::LARGER) std::swap(u, v);
    }

    bool operator<(const Edge& other) const {
        return std::tie(u, v, weight) < std::tie(other.u, other.v, other.weight);
    };
};

struct Graph {
    std::set<Point> vertices;
    std::set<Edge> edges;
};

#endif // GRAPH_H
