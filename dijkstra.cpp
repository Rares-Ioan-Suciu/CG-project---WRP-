#include "dijkstra.h"


// this file contains a simple implementation of the Dijkstra algorithm for computing the shortest paths
// we pass as arugments the graph, the source, the destination and the stream to a file that will save
// the path found by this algo and the shortest distance
double dijkstra(const Graph& discreted_graph, const Point& sourcePoint, const Point& destPoint, std::ofstream& saveFile) {

    std::map<Point, double> distanceMap;
    std::map<Point, Point> predMap;
    // we use two maps one that connects a point to the shortest shortestPathfrom source to it, and one that remebers the pred of the point
    using PQElement = std::pair<double, Point>;
    std::priority_queue<PQElement, std::vector<PQElement>, std::greater<>> pq;
   // to make the algorithm more efficent we add all the elements on a priority queue
    for (const auto& node : discreted_graph.vertices) {
        distanceMap[node] = std::numeric_limits<double>::infinity();
    } // initially everything is on infinity

    distanceMap[sourcePoint] = 0.0;
    pq.emplace(0.0, sourcePoint);
    // we put the source on the priorty queue and start the main loop of the algo

    while (!pq.empty()) {
        // get the current elemetn and the distance from the source
        auto [current_distance, current_point] = pq.top();
        pq.pop();


        if (current_point == destPoint)
            break;

        for (const auto& edge : discreted_graph.edges) {
            if (edge.u == current_point || edge.v == current_point) {
                Point neighbor = (edge.u == current_point) ? edge.v : edge.u;
                double new_distance = current_distance + edge.weight;
                // if we find a neighbout to our current point and the
                // new distance is shorter than the previously recorded distance for the neighbor, we update the diatance for said neighbour
                if (new_distance < distanceMap[neighbor]) {
                    distanceMap[neighbor] = new_distance;
                    predMap[neighbor] = current_point;
                    pq.emplace(new_distance, neighbor);
                }
            }
        }
    }

    if (distanceMap[destPoint] == std::numeric_limits<double>::infinity()) {
        std::cout << "No shortest path found from sourcePoint to destination." << std::endl;
        return std::numeric_limits<double>::infinity();
    }

    std::vector<Point> shortestPath;
    for (Point at = destPoint; at != sourcePoint; at = predMap[at])
    {
        shortestPath.push_back(at);
    }
    shortestPath.push_back(sourcePoint);

    // reverse the shortestPath to get it from source to destination
    std::reverse(shortestPath.begin(), shortestPath.end());

    if(!saveFile.is_open()) {
      std::cerr << "Could not open file " << std::endl;
    }
    saveFile<< "Shortest path from source to destination:" << std::endl;
        for (const auto& node : shortestPath)
     {
        saveFile<< node << " ";
     }
    saveFile<< "\nTotal distance: " << distanceMap[destPoint] << std::endl;
    return distanceMap[destPoint];
}
