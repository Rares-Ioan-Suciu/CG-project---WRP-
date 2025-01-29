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
#include "experimentPart.h"
#include <string.h>

std::vector<Point> points;
std::vector<triangle_face> faces;

Graph G1; // simple discretization
Graph G2; // + midpoints and centroid
Graph G3; // barycentric
Graph G4; // barycentric Weighted
Graph G5; // density Based
Point source, destination;
Delaunay dt; // delaunay trinagulation Object dn source and destination for later use

std::string save_file = "/home/rares655/test_project/triangulationAndWay"; // FILE to save visualization
// PLEASE save with own file path when trying to run the code, otherwise it won t work. Additionaly when
//trying to visualize in the python script, also use that path there

void validate_arguments(int argc, int expected, const std::string& usage_message) {
    if (argc != expected) {
        std::cerr << usage_message << std::endl;
        exit(1);
    }
}

int main(int argc, const char *argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <Mode: input/random/directly> <additional arguments...>" << std::endl;
        exit(1);
    }

    std::string mode = argv[1];

    if (mode == "visualization") {
        std::cout << "Entered visualization mode\n"; // the main handles two main cases - visualization, when we only want to get one triangualtion with all methods
        //and experiment in which we get data from running a particular set of methods and algos
        if (strcmp(argv[2], "input") == 0) { // the user provides a file with points
            points = read_points(argv[3]);
            auto result = triangulate(points);
            faces = result.first;
            dt = result.second;
        } else if (strcmp(argv[2], "random_simple") == 0) { // we generate n random points in the plane and then do the delaunay trig
            int no_points = atoi(argv[3]);
            if (no_points <= 0) {
                std::cerr << "Number of points should be greater than 0" << std::endl;
                exit(1);
            }
            points = read_random_points(no_points);
            auto result = triangulate(points);
            faces = result.first;
            dt = result.second;
        } else if (strcmp(argv[2], "random_skewed") == 0) { //we generate n random skewed points in the plane and then do the delaunay trig
            int no_points = atoi(argv[3]);
            if (no_points <= 0) {
                std::cerr << "Number of points should be greater than 0" << std::endl;
                exit(1);
            }
            points = generate_skewed(no_points);
            auto result = triangulate(points);
            faces = result.first;
            dt = result.second;

        } else if (strcmp(argv[2], "random_cluster") == 0) { //we generate n random clustered points in the plane and then do the delaunay trig
            int no_points = atoi(argv[3]);
            if (no_points <= 0) {
                std::cerr << "Number of points should be greater than 0" << std::endl;
                exit(1);
            }
            int no_clusters = std::max(1, no_points / 20);
            int points_per_cluster = std::max(1, no_points / no_clusters);
            double cluster_radius_min = std::max(0.1, 0.05 * points_per_cluster);
            double cluster_radius_max = std::max(cluster_radius_min * 2, 0.1 * points_per_cluster);
            double gap_min = std::max(5.0, cluster_radius_max * 2);
            double gap_max = std::max(gap_min * 2, gap_min + 10.0);

            points = generate_clusters(no_clusters, points_per_cluster, gap_max);
            auto result = triangulate(points);
            faces = result.first;
            dt = result.second;

        } else if (strcmp(argv[2], "random_boundary_points") == 0) {
            int no_points = atoi(argv[3]);
            if (no_points <= 0) {
                std::cerr << "Number of points should be greater than 0" << std::endl;
                exit(1);
            }
            points = generate_boundary_points(no_points);
            auto result = triangulate(points);
            faces = result.first;
            dt = result.second;

        } else if (strcmp(argv[2], "directly") == 0) { // triangulation is directly provided by the user, each trangle with it s vertices and with its weight
            std::string filename = argv[3];
            std::ifstream file(filename);

            if (!file.is_open()) {
                std::cerr << "Error opening file: " << filename << std::endl;
                exit(1);
            }

            std::string line;
            while (std::getline(file, line)) {
                std::istringstream stream(line);
                triangle_face face;
                if (stream >> face.vertex[0] >> face.vertex[1] >> face.vertex[2] >> face.weight) {
                    faces.push_back(face);
                }
            }
        }


        std::ofstream file(save_file);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << save_file << std::endl;
            exit(1);
        }

        file << "Triangles:\n";
        for (const auto& face : faces) {
            file << face.vertex[0] << " " << face.vertex[1] << " " << face.vertex[2] << " " << face.weight << std::endl;
        }

        // after getting the points from one of teh mehtods above, we generate the source and the destination inside the triangualtion at random
        // I did this in order to get some more interesting cases, rather than always have source and detsination as triangle vertices
        get_random_source_destination(dt, source, destination);

        G1 = simple_discretization(faces);
        attach_point_to_graph(G1, source, destination, faces);
        dijkstra(G1, source, destination, file);

        G2 = triangle_points(faces);
        attach_point_to_graph(G2, source, destination, faces);
        dijkstra(G2, source, destination, file);

        G3 = barycentric_points(faces);
        attach_point_to_graph(G3, source, destination, faces);

        dijkstra(G3, source, destination, file);

        G4 = weightedBarycentric(faces);
        attach_point_to_graph(G4, source, destination, faces);
        dijkstra(G4, source, destination, file);

        G5 = weightedDensity(faces);
        attach_point_to_graph(G5, source, destination, faces);
        dijkstra(G5, source, destination, file);

        // we get run the discretization for each of the 5 methods and then run dijkstra to get the path and the distance, those are written in th
        // triangulationAndWay file to use in the visualziation script
    }else if (mode == "random_simple") { // now we enter the experiment territoy where for each method to generate points we validate arguments
    // arguments shoudl not be any problem as these are hard-coded in the pythons scirpt, then actually run the expoerimetn
      validate_arguments(argc, 6, "Usage: " + std::string(argv[0]) + " random_simple <no_points> <discretization> <pathfinding_algorithm> <output_file>");
      int no_points = std::stoi(argv[2]);
      if (no_points <= 0) {
          std::cerr << "Number of points should be greater than 0" << std::endl;
          exit(1);
      }
      points = read_random_points(no_points);
      run_experiment(points, argv[3], argv[4], no_points, argv[5]);

    } else if (mode == "random_skewed") { // skewed points baby
        validate_arguments(argc, 6, "Usage: " + std::string(argv[0]) + " random_skewed <no_points> <discretization> <pathfinding_algorithm> <output_file>");
        int no_points = std::stoi(argv[2]);
        if (no_points <= 0) {
            std::cerr << "Number of points should be greater than 0" << std::endl;
            exit(1);  // Exit if invalid input
        }
        points = generate_skewed(no_points);
        run_experiment(points, argv[3], argv[4], no_points, argv[5]);

    } else if (mode == "random_cluster") {  // everything in one place mode
        validate_arguments(argc, 6, "Usage: " + std::string(argv[0]) + " random_cluster <no_points> <discretization> <pathfinding_algorithm> <output_file>");
        int no_points = std::stoi(argv[2]);
        if (no_points <= 0) {
            std::cerr << "Number of points should be greater than 0" << std::endl;
            exit(1);  // Exit if invalid input
        }
        int no_clusters = std::max(1, no_points / 20);
        int points_per_cluster = std::max(1, no_points / no_clusters);
        double cluster_radius_min = std::max(0.1, 0.05 * points_per_cluster);
        double cluster_radius_max = std::max(cluster_radius_min * 2, 0.1 * points_per_cluster);
        double gap_max = std::max(10.0, cluster_radius_max * 2);
        points = generate_clusters(no_clusters, points_per_cluster, gap_max);
        run_experiment(points, argv[3], argv[4], no_points, argv[5]);
    } else if (mode == "random_boundary_points") { // points on a boundary
        validate_arguments(argc, 6, "Usage: " + std::string(argv[0]) + " random_boundary_points <no_points> <discretization> <pathfinding_algorithm> <output_file>");
        int no_points = std::stoi(argv[2]);
        if (no_points <= 0) {
            std::cerr << "Number of points should be greater than 0" << std::endl;
            exit(1);
        }
        points = generate_boundary_points(no_points);
        run_experiment(points, argv[3], argv[4], no_points, argv[5]);
    } else { // none of the usaual modes, if we get to this then we must have made a spelling error in the python script
        std::cerr << "Invalid mode: " << mode << std::endl;
        exit(1);
    }
    return 0;
}
