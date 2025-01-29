#include "discretization.h"
#include <cmath>
#include <optional>



// in this file we declare and implement the 5 different discretization methods, wehre given a set of triangle faces with weights
// we build a weighted graph in order to apply shortest path algo on them

double getEuclid(const Point &P, const Point &Q) {
  return std::sqrt(CGAL::squared_distance(P, Q));
}

void cleanUpper(Graph& graph) { // I did this helper funciton in order to ensure no edge appears twice in the simple_graph
// this kept happening becasue we have edges with same endpoints but different weight, in that case we want to keep the one with smaller weight
    std::vector<Edge> edges(graph.edges.begin(), graph.edges.end());

        for (int i = 0; i < edges.size(); ++i)
    {
        for (int j = 0; j < i; ++j) {
            if ((edges[i].u == edges[j].u && edges[i].v == edges[j].v) || (edges[i].u == edges[j].v && edges[i].v == edges[j].u))
           {
                if (edges[i].weight > edges[j].weight)
                {
                    edges.erase(edges.begin() + i);
                    i--;
                    break;
                }
                else
                {
                    edges.erase(edges.begin() + j);
                    i--;
                    break;
                }
           }
    }
}

    graph.edges = std::set<Edge>(edges.begin(), edges.end());
}



Graph simple_discretization(const std::vector<triangle_face>& faces) {
    Graph simple_graph;
    for (const auto& face : faces) {
        for (const auto& vertex : face.vertex)
      {
        simple_graph.vertices.insert(vertex);
      }

       // thsi is the simplest discretization method where we add to the graph the vertices and edges of each triangle face as nodes and graph edges
       // this lines of code will keep appearing in the other methods as we always apply this connectivity inside all other methods
        for (int i = 0; i < 3; ++i)
      {
            for (int j = i + 1; j < 3; ++j)
           {
                 double squared_length = getEuclid(face.vertex[i], face.vertex[j]);
                 double weight = face.weight*squared_length;

                 Edge edge(face.vertex[i], face.vertex[j], weight);
                 auto iterator = simple_graph.edges.find(edge);
                        if (iterator == simple_graph.edges.end())
                 {
                            simple_graph.edges.insert(edge);
                 }
                        else if (edge.weight < iterator->weight)
                 {
                        simple_graph.edges.erase(iterator);
                        simple_graph.edges.insert(edge);
                 }

           }
      }
    }
    cleanUpper(simple_graph); // we always clean up the graph and then return it
    return simple_graph;
}

Point calculateCentroid(const triangle_face& face) {
    return Point((face.vertex[0].x() + face.vertex[1].x() + face.vertex[2].x()) / 3.0,(face.vertex[0].y() + face.vertex[1].y() + face.vertex[2].y()) / 3.0);
}

std::array<Point, 3> calculateMidpoints(const triangle_face& face) {
    std::array<Point, 3> midpoints;

    midpoints[0] = Point((face.vertex[0].x() + face.vertex[1].x()) / 2.0, (face.vertex[0].y() + face.vertex[1].y()) / 2.0);
    midpoints[1] = Point((face.vertex[1].x() + face.vertex[2].x()) / 2.0, (face.vertex[1].y() + face.vertex[2].y()) / 2.0);
    midpoints[2] = Point((face.vertex[2].x() + face.vertex[0].x()) / 2.0, (face.vertex[2].y() + face.vertex[0].y()) / 2.0);

    return midpoints;
}

void addEdgesFromMidpointsToVertices(const triangle_face& face,const std::array<Point, 3>& midpoints, Graph& simple_graph)
{
  // we compute and add the new edges for the first of the midpoints
    double weight0 = face.weight * getEuclid(midpoints[0], face.vertex[0]);
    simple_graph.edges.insert(Edge(midpoints[0], face.vertex[0], weight0));

    double weight1 = face.weight * getEuclid(midpoints[0], face.vertex[1]);
    simple_graph.edges.insert(Edge(midpoints[0], face.vertex[1], weight1));

    double weight2 = face.weight * getEuclid(midpoints[0], face.vertex[2]);
    simple_graph.edges.insert(Edge(midpoints[0], face.vertex[2], weight2));

    double weight3 = face.weight * getEuclid(midpoints[0], midpoints[1]);
    simple_graph.edges.insert(Edge(midpoints[0], midpoints[1], weight3));

    double weight4 = face.weight * getEuclid(midpoints[0], midpoints[2]);
    simple_graph.edges.insert(Edge(midpoints[0], midpoints[2], weight4));

  // we compute and add the new edges for the seconf of the midpoints
    double weight5 = face.weight * getEuclid(midpoints[1], face.vertex[0]);
    simple_graph.edges.insert(Edge(midpoints[1], face.vertex[0], weight5));

    double weight6 = face.weight * getEuclid(midpoints[1], face.vertex[1]);
    simple_graph.edges.insert(Edge(midpoints[1], face.vertex[1], weight6));

    double weight7 = face.weight * getEuclid(midpoints[1], face.vertex[2]);
    simple_graph.edges.insert(Edge(midpoints[1], face.vertex[2], weight7));

    double weight8 = face.weight * getEuclid(midpoints[1], midpoints[2]);
    simple_graph.edges.insert(Edge(midpoints[1], midpoints[2], weight8));

 // and now we do the last of the midpoints
    double weight9 = face.weight * getEuclid(midpoints[2], face.vertex[0]);
    simple_graph.edges.insert(Edge(midpoints[2], face.vertex[0], weight9));

    double weight10 = face.weight * getEuclid(midpoints[2], face.vertex[1]);
    simple_graph.edges.insert(Edge(midpoints[2], face.vertex[1], weight10));

    double weight11 = face.weight * getEuclid(midpoints[2], face.vertex[2]);
    simple_graph.edges.insert(Edge(midpoints[2], face.vertex[2], weight11));
}



void addEdgesToCentroid(const triangle_face& face ,const std::array<Point, 3>& midpoints, const Point& centroid,Graph& graph)
{

    // we connect the centorid point that we found to the midpoints and the vertices of the triangle face it belongs to
    double weight0 = face.weight * getEuclid(midpoints[0], centroid);
    graph.edges.insert(Edge(midpoints[0], centroid, weight0));

    double weight1 = face.weight * getEuclid(midpoints[1], centroid);
    graph.edges.insert(Edge(midpoints[1], centroid, weight1));

    double weight2 = face.weight * getEuclid(midpoints[2], centroid);
    graph.edges.insert(Edge(midpoints[2], centroid, weight2));

    double weight3 = face.weight * getEuclid(face.vertex[0], centroid);
    graph.edges.insert(Edge(face.vertex[0], centroid, weight3));

    double weight4 = face.weight * getEuclid(face.vertex[1], centroid);
    graph.edges.insert(Edge(face.vertex[1], centroid, weight4));

    double weight5 = face.weight * getEuclid(face.vertex[2], centroid);
    graph.edges.insert(Edge(face.vertex[2], centroid, weight5));
}

Graph triangle_points(const std::vector<triangle_face>& faces) {
    Graph triangle_graph;
    //  in this discretization methdo in order to subidivide the traingle faces we add the midpoints of the edges and the centorid
    // basically we are offering new ways to traversing a face, giving the chance to get out of it, if it has a big weight or
    // go through it, if it has a small weight
    for (const auto& face : faces)
    {
        for (const auto& vertex : face.vertex)
      {
            triangle_graph.vertices.insert(vertex);
      }
        for (int i = 0; i < 3; ++i)
        {
            for (int j = i + 1; j < 3; ++j)
            {
                double squared_length = getEuclid(face.vertex[i], face.vertex[j]);
                double weight = face.weight*squared_length;

                Edge edge(face.vertex[i], face.vertex[j], weight);
                auto iterator = triangle_graph.edges.find(edge);
                if (iterator == triangle_graph.edges.end())
                {
                    triangle_graph.edges.insert(edge);
                }
                else if (edge.weight < iterator->weight)
                {
                    triangle_graph.edges.erase(iterator);
                    triangle_graph.edges.insert(edge);
                }

            }
        }
        auto midpoints = calculateMidpoints(face);
        for (const auto& midpoint : midpoints)
        {
            triangle_graph.vertices.insert(midpoint);
        }

        Point centroid = calculateCentroid(face);
        triangle_graph.vertices.insert(centroid);


        addEdgesFromMidpointsToVertices(face, midpoints, triangle_graph);
        addEdgesToCentroid(face, midpoints, centroid, triangle_graph);
    }  // add the midpoints + centoird, connect them to everything, clean the graph and the return
    cleanUpper(triangle_graph);
    return triangle_graph;
}

std::vector<Point> generateRandomPoints(const triangle_face& face, int count) {
    std::vector<Point> randomPoints;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    for (int i = 0; i < count; ++i) {
        float u, v, w;
        do {
            u = dis(gen);
            v = dis(gen);
            w = 1.0f - u - v;
        } while (u < 0 || v < 0 || w < 0);
        // we keep generating random real numbers until the condition is satisfied, this way we make sure that the new radnom point is insdie the traingle
        Point randomPoint(u * face.vertex[0].x() + v * face.vertex[1].x() + w * face.vertex[2].x(),u * face.vertex[0].y() + v * face.vertex[1].y() + w * face.vertex[2].y());
        randomPoints.push_back(randomPoint);
    }

    return randomPoints;
}

void addNewPointsToGraph(const triangle_face& face, const std::vector<Point>& newPoints, Graph& graph) {

    for (const auto& vertex : face.vertex) {
        graph.vertices.insert(vertex);
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = i + 1; j < 3; ++j) {
            double weight = face.weight * getEuclid(face.vertex[i], face.vertex[j]);
            Edge edge(face.vertex[i], face.vertex[j], weight);

            auto it = graph.edges.find(edge);
            if (it == graph.edges.end()) {
                graph.edges.insert(edge);
            } else if (edge.weight < it->weight) {
                graph.edges.erase(it);
                graph.edges.insert(edge);
            }
        }
    }

    for (const auto& point : newPoints) {
        graph.vertices.insert(point);
    }

    // we add the vertices of the triangle to the graph, alonside the edges, then we connect the newpoints added to the triangle face to the vertices
    // in the end we connect all points betweeen them
    for (int i = 0; i < newPoints.size(); ++i) {
        double weight = face.weight * getEuclid(face.vertex[i % 3], newPoints[i]);
        graph.edges.insert(Edge(face.vertex[i % 3], newPoints[i], weight));
    }
    for (int i = 0; i < newPoints.size(); ++i) {
        for (int j = i + 1; j < newPoints.size(); ++j) {
            double weight = face.weight * getEuclid(newPoints[i], newPoints[j]);
            graph.edges.insert(Edge(newPoints[i], newPoints[j], weight));
        }
    }
}



Graph barycentric_points(const std::vector<triangle_face>& faces) {
    Graph barycentricGraph;

    for (const auto& face : faces)
    {
        auto newPoints = generateRandomPoints(face, 10);
        addNewPointsToGraph(face, newPoints, barycentricGraph);
    }  // we use this method in order to generate ranodm points inside a traingle face, the only problem is that to get good results
    // we must add around 10 points... which is hell on mmemory

    cleanUpper(barycentricGraph);
    return barycentricGraph;
}


Graph weightedBarycentric(const std::vector<triangle_face>& faces, int min_points, int max_points) {
    Graph barycentricGraph;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    for (const auto& face : faces) {
        // I came up with the idea for this method with the hope of adding less random points
        // basically we look at the normalized weight of the traingle face and depeding on that
        // we add more or less ranodm points to the triangle face, the number of points is the only difference from the
        // previous method
        double normalized_weight = (face.weight - 0.0) / (50 - 1);
        int N_points = static_cast<int>(min_points + normalized_weight * (max_points - min_points));
        std::vector<Point> newPoints;
        for (int i = 0; i < N_points; ++i) {
            double u, v, w;
            do {
                u = dis(gen);
                v = dis(gen);
                w = 1.0 - u - v;
            } while (u < 0 || v < 0 || w < 0);

            Point randomPoint(u * face.vertex[0].x() + v * face.vertex[1].x() + w * face.vertex[2].x(),u * face.vertex[0].y() + v * face.vertex[1].y() + w * face.vertex[2].y());
            newPoints.push_back(randomPoint);
        }

        for (const auto& vertex : face.vertex) {
            barycentricGraph.vertices.insert(vertex);
        }

        for (int i = 0; i < 3; ++i) {
            for (int j = i + 1; j < 3; ++j) {
                double weight = face.weight * getEuclid(face.vertex[i], face.vertex[j]);
                Edge edge(face.vertex[i], face.vertex[j], weight);

                auto it = barycentricGraph.edges.find(edge);
                if (it == barycentricGraph.edges.end()) {
                    barycentricGraph.edges.insert(edge);
                } else if (edge.weight < it->weight) {
                    barycentricGraph.edges.erase(it);
                    barycentricGraph.edges.insert(edge);
                }
            }
        }

        for (const auto& point : newPoints) {
            barycentricGraph.vertices.insert(point);
        }
        for (const auto& point : newPoints) {
            for (int i = 0; i < 3; ++i) {
                double weight = face.weight * getEuclid(face.vertex[i], point);
                barycentricGraph.edges.insert(Edge(face.vertex[i], point, weight));
            }
        }

        // we connect the points to each other and to the vertices, putting the edges along the way
        for (int i = 0; i < newPoints.size(); ++i) {
            for (int j = i + 1; j < newPoints.size(); ++j) {
                double weight = face.weight * getEuclid(newPoints[i], newPoints[j]);
                barycentricGraph.edges.insert(Edge(newPoints[i], newPoints[j], weight));
            }
        }
    }
    cleanUpper(barycentricGraph); // we always clean up after ourselves
    return barycentricGraph;
}

Graph weightedDensity(const std::vector<triangle_face>& faces, double max_density) {
    Graph density_graph;

    for (const auto& face : faces) {

        double normalized_weight = (face.weight - 0.0) / (50 - 1.0);
        double density = normalized_weight * max_density;
        int grid_size = std::min(4, static_cast<int>(density * 2));
        // in this method we compute the grid size, i.e. how many points we should add to the graph based on the 'density' of the traingle face
        // this is another method we we want to subdivide the traingle using random points, that we add inside them
        for (const auto& vertex : face.vertex) {
            density_graph.vertices.insert(vertex);
        }

        for (int i = 0; i < 3; ++i) {
            for (int j = i + 1; j < 3; ++j) {
                double weight = face.weight * getEuclid(face.vertex[i], face.vertex[j]);
                Edge edge(face.vertex[i], face.vertex[j], weight);
                auto it = density_graph.edges.find(edge);
                if (it == density_graph.edges.end()) {
                    density_graph.edges.insert(edge);
                } else if (edge.weight < it->weight) {
                    density_graph.edges.erase(it);
                    density_graph.edges.insert(edge);
                }
            }
        }

        std::vector<Point> newPoints;
        for (int i = 0; i <= grid_size; ++i) {
            for (int j = 0; j <= grid_size - i; ++j) {
                double u = i / static_cast<double>(grid_size);
                double v = j / static_cast<double>(grid_size);
                double w = 1.0 - u - v;

                Point randomPoint(u * face.vertex[0].x() + v * face.vertex[1].x() + w * face.vertex[2].x(),u * face.vertex[0].y() + v * face.vertex[1].y() + w * face.vertex[2].y());

                newPoints.push_back(randomPoint);
                density_graph.vertices.insert(randomPoint);


                for (const auto& vertex : face.vertex) {
                    double weight = face.weight * getEuclid(randomPoint, vertex);
                    density_graph.edges.insert(Edge(randomPoint, vertex, weight));
                }
            }
        }

        for (int i = 0; i < newPoints.size(); ++i) {
            for (int j = i + 1; j < newPoints.size(); ++j) {
                double weight = face.weight * getEuclid(newPoints[i], newPoints[j]);
                density_graph.edges.insert(Edge(newPoints[i], newPoints[j], weight));
            }
        }
    }
    cleanUpper(density_graph); // always clean after yoursef
    return density_graph;
}














