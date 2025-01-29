//
// Created by rares655 on 12/30/24.
//

#ifndef READ_POINTS_H
#define READ_POINTS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <ctime>
#include <string>
#include <random>
#include <ctime>
#include "graph.h"
#include "delaunay_trig.h"

typedef CGAL::Simple_cartesian<double> Kernel;
typedef Kernel::Point_2 Point;
typedef CGAL::Delaunay_triangulation_2<Kernel> Delaunay;

std::vector<Point> read_points(const std::string& filename);
std::vector<Point> read_random_points(int num_points, double range_min = -2500, double range_max = 2500);
std::vector<Point> generate_skewed(int num_points, double x_min=-5000, double x_max=5000, double y_min=-4500, double y_max=4500);
std::vector<Point> generate_clusters(int clusters, int points_per_cluster, double gap_size);
std::vector<Point> generate_boundary_points(int num_points, double x_min=-2500, double x_max=4000, double y_min=-5000, double y_max=7530);
void get_random_source_destination(const Delaunay& dt, Point& source, Point& destination);
void attach_point_to_graph(Graph& graph, const Point& source, const Point& destination, const std::vector<triangle_face>& faces);
#endif //READ_POINTS_H

