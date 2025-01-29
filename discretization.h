#ifndef DISCRETIZATION_H
#define DISCRETIZATION_H

#include <CGAL/Simple_cartesian.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <vector>
#include <map>
#include <set>
#include "delaunay_trig.h"
#include "graph.h"
#include <CGAL/Vector_2.h>
#include <CGAL/Line_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Polygon_2_algorithms.h>

typedef CGAL::Simple_cartesian<double> Kernel;

void addEdgesToCentroid(const triangle_face& face ,const std::array<Point, 3>& midpoints, const Point& centroid,Graph& graph);
void addEdgesFromMidpointsToVertices(const triangle_face& face,const std::array<Point, 3>& midpoints, Graph& graph);
Point calculateCentroid(const triangle_face& face);
void cleanUpper(Graph& graph);
double getEuclid(const Point &P, const Point &Q);
Graph weightedBarycentric(const std::vector<triangle_face>& faces, int min_points=3, int max_points=5);
Graph weightedDensity(const std::vector<triangle_face>& faces, double max_density=3);
Graph simple_discretization(const std::vector<triangle_face>& faces);
Graph triangle_points(const std::vector<triangle_face>& faces);
Graph barycentric_points(const std::vector<triangle_face>& faces);



#endif // DISCRETIZATION_H
