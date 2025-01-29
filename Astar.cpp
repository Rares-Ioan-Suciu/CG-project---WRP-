//
// Created by rares655 on 1/25/25.
//

#include "Astar.h"

// this file contains a simple implementation of the A* algorithm using the heuristic of the Euclidean distance as estiamted cost for computing the shortest paths
// we pass as arugments the graph, the source, the destination and the stream to a file that will save
// the path found by this algo and the shortest distance

double euclidean_distance(const Point& a, const Point& b) {
    return std::sqrt(CGAL::squared_distance(a, b));
 }

double a_star(const Graph& discretedGraph, const Point& source, const Point& dest, std::ofstream& saveFile)
{
    std::map<Point, double> shortest_dis;  // map to store pair of points and cost to get to said point
    std::map<Point, double> estimated_cost;  // the estiamted cost using very simple euristics of the euclidean distance
    std::map<Point, Point> predecessors;  // a third map to store the predecesors of a point in the graph


    using PQElement = std::pair<double, Point>;
    std::priority_queue<PQElement, std::vector<PQElement>, std::greater<>> pq;
    // we will use a priority queue for efficency of the algo just as we did in Dijsktra
    for (const auto& vertex : discretedGraph.vertices) {
        shortest_dis[vertex] = std::numeric_limits<double>::infinity();  // shortest_dis stores the shortest distance from source
        estimated_cost[vertex] = std::numeric_limits<double>::infinity();  // estimated_cost will store the estimated distacne using euclidean distance
    }


    shortest_dis[source] = 0.0;
    estimated_cost[source] = euclidean_distance(source, dest);
    pq.emplace(estimated_cost[source], source);


   // we put the source on the queue and start executing the main loop
    while (!pq.empty()) {
        auto [current_f_cost, current_point] = pq.top();
        pq.pop();

         if (current_point == dest) {
            break;
        }

        for (const auto& edge : discretedGraph.edges) {
            if (edge.u == current_point || edge.v == current_point) {
                Point neighbor = (edge.u == current_point) ? edge.v : edge.u;


                //compute the tentative shortest distance to reach neighbour through point
                double tentative_distance = shortest_dis[current_point] + edge.weight;

                // if the tentative shortest distance is lower than the previously recorded shortest path for the neighbor we update the shortest path
                if (tentative_distance < shortest_dis[neighbor]) {
                    shortest_dis[neighbor] = tentative_distance
;
                    // additionally we updatet the estimated distance using the euclidean distance
                    estimated_cost[neighbor] = shortest_dis[neighbor] + euclidean_distance(neighbor, dest);
                    predecessors[neighbor] = current_point;
                    pq.emplace(estimated_cost[neighbor], neighbor);
                }
            }
        }
    }


    if (shortest_dis[dest] == std::numeric_limits<double>::infinity()) {
        std::cerr << "No path found from source to destination." << std::endl;
        return std::numeric_limits<double>::infinity();
    }


    std::vector<Point> path;
    for (Point at = dest; at != source; at = predecessors[at]) {
        path.push_back(at);
    }
    path.push_back(source);

    // we reverse the path to get the points in order source -> destination
    std::reverse(path.begin(), path.end());

    if (!saveFile.is_open()) {
        std::cerr << "Could not open file to write the path." << std::endl;
        return std::numeric_limits<double>::infinity();
    }
    saveFile << "Shortest path from source to destination:" << std::endl;
    for (const auto& point : path) {
        saveFile << point << " ";  // Print each point in the path
    }
    saveFile << "\nTotal distance: " << shortest_dis[dest] << std::endl;  // Print the total distance from source to destination

    return shortest_dis[dest];  // Return the total distance from source to destination
}
