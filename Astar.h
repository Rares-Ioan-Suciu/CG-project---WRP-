//
// Created by rares655 on 1/26/25.
//
#ifndef ASTAR_H
#define ASTAR_H

#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include "discretization.h"
#include "graph.h"
#include "delaunay_trig.h"


double euclidean_distance(const Point& a, const Point& b);
double a_star(const Graph& graph, const Point& source, const Point& dest, std::ofstream& log);


#endif //ASTAR_H
