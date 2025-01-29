//
// Created by rares655 on 1/26/25.
//

#ifndef EXPERIMENTPART_H
#define EXPERIMENTPART_H

#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include "dijkstra.h"
#include "discretization.h"
#include "delaunay_trig.h"
#include "read_points.h"
#include "graph.h"
#include "Astar.h"

void run_experiment(std::vector<Point>& points, const std::string& discretization_method, const std::string& pathfinding_algorithm, int no_points, const std::string& save_file);

#endif //EXPERIMENTPART_H
