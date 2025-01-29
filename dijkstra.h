//
// Created by rares655 on 1/01/25.
//
#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <vector>
#include <limits>
#include <queue>
#include <iostream>
#include <fstream>
#include "discretization.h"
#include "graph.h"
#include "delaunay_trig.h"

double dijkstra(const Graph& discreted_graph, const Point& source, const Point& dest, std::ofstream& log);
#endif // DIJKSTRA_H
