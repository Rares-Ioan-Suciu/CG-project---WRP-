//
// Created by rares655 on 1/26/25.
//

#include "experimentPart.h"
#include <iomanip>

void run_experiment(std::vector<Point>& points, const std::string& discretization_method, const std::string& pathfinding_algorithm, int no_points, const std::string& save_file) {

    auto result = triangulate(points);
    auto faces = result.first;
    auto dt = result.second;

    Graph G;
    if (discretization_method == "simple") {
        G = simple_discretization(faces);
    } else if (discretization_method == "midpoints") {
        G = triangle_points(faces);
    } else if (discretization_method == "barycentric") {
        G = barycentric_points(faces);
    } else if (discretization_method == "barycentricWeight") {
        G = weightedBarycentric(faces);
    } else if (discretization_method == "densityWeight") {
        G = weightedDensity(faces);
    }
    else {
        std::cerr << "Unknown discretization method: " << discretization_method << std::endl;
        exit(1);
    }

    Point source, destination;
    get_random_source_destination(dt, source, destination);
    attach_point_to_graph(G, source, destination, faces);

    double shortest_path_length = 0.0;

    std::ofstream log_file("/home/rares655/test_project/triangulationAndWay");
    if (!log_file.is_open()) {
        std::cerr << "Error opening file for writing path results!" << std::endl;
        exit(1);
    }
    auto start_time = std::chrono::high_resolution_clock::now();

    if (pathfinding_algorithm == "dijkstra") {
        shortest_path_length = dijkstra(G, source, destination, log_file);
    } else if (pathfinding_algorithm == "astar") {
        shortest_path_length = a_star(G, source, destination, log_file);
    } else {
        std::cerr << "Unknown pathfinding algorithm: " << pathfinding_algorithm << std::endl;
        exit(1);
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count(); // Use microseconds

    ssize_t memory_usage = G.vertices.size() * sizeof(Point) + G.edges.size() * sizeof(Edge);


    std::ofstream file(save_file, std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Error opening output file: " << save_file << std::endl;
        exit(1);
    }

    file << no_points << ","<< memory_usage << "," << shortest_path_length << ","<<std::fixed << std::setprecision(6)<< duration / 1000.0 << " ms" << std::endl; // Convert microseconds to milliseconds
    file.close();

    log_file.close();
}

