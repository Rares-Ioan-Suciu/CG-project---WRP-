//
// Created by rares655 on 12/30/24.
//

#include "delaunay_trig.h"

// we use this function to  get thr triangle faces from the Cgal delaunay trig
// each trig face contains three vertices and the weight associated, we use the random to generate a value from
// 1 to 50 as weights, this range can be changed, but I tried to obtain very long paths as it added nothing to the implementaitn

std::pair<std::vector<triangle_face>, Delaunay> triangulate(const std::vector<Point> &vertices) {
    std::vector<triangle_face> triangle_faces;
    Delaunay triangulation;  // the delauany type is brought from CGAL and I defined it in the delaunay_trig.h
    triangulation.insert(vertices.begin(), vertices.end()); // this cgal method computes the delaunay triangualtion given a set of points

    std::random_device getRandom;
    std::mt19937 gen(getRandom());
    std::uniform_real_distribution<> dis(1, 50);

    for (auto f = triangulation.finite_faces_begin(); f != triangulation.finite_faces_end(); ++f) {
        triangle_face tf;
        tf.vertex[0] = f->vertex(0)->point();
        tf.vertex[1] = f->vertex(1)->point();
        tf.vertex[2] = f->vertex(2)->point();
        tf.weight = static_cast<float>(dis(gen));
        triangle_faces.push_back(tf);
    }

    return {triangle_faces, triangulation}; // we retunr the traingles faces and the triangulation for later use in the main.cpp file
}