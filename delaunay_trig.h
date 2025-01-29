//
// Created by rares655 on 12/30/24.
//

#ifndef DELAUNAY_TRIG_H
#define DELAUNAY_TRIG_H

#include <CGAL/Simple_cartesian.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <vector>
#include <map>
#include <random>
#include <set>


// in this file we define the cgal types we are using in order to ease our computations
typedef CGAL::Simple_cartesian<double> Kernel;
typedef CGAL::Delaunay_triangulation_2<Kernel> Delaunay;
typedef Kernel::Point_2 Point;
// additionally we define the struct triangle_face that will hold the vertices of a triangle and it's assoiated weight
struct triangle_face {
    Point vertex[3];
    int weight;

    bool compare(const triangle_face &f) const {
        return vertex[0].x() == f.vertex[0].x() && vertex[1].x() == f.vertex[1].x() && vertex[2].x() == f.vertex[2].x()
               && vertex[0].y() == f.vertex[0].y() && vertex[1].y() == f.vertex[1].y() && vertex[2].y() == f.vertex[2].y()
               && weight == f.weight;
    }
};


std::pair<std::vector<triangle_face>, Delaunay> triangulate(const std::vector<Point> &vertices);

#endif //DELAUNAY_TRIG_H
