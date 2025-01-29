//
// Created by rares655 on 12/30/24.
//

#include "read_points.h"

// this file contains all the implementations of the reading/ generating points or trianglations
// basically here is where the input for the program is generated
//additionally we have some other functions like attach_point + get_source_destination to make sure the points source and destination are connected to the graph

std::vector<Point> read_points(const std::string& filename) {
    std::vector<Point> points;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return points;
    }
    double x, y;
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream stream(line);
        if (stream >> x >> y) {
            points.push_back(Point(x, y));
        } // I presume the file given for input simpley contains two float values on a line, one pair a line, that we add to a vector and we return
    }
    file.close();
    return points;
}

std::vector<Point> read_random_points(int num_points, double range_min, double range_max) {
    if (range_min > range_max) {
        std::swap(range_min, range_max); // we generate n random points usinf random_device from the standard library, ensuring a certain range
    } // I used the range in order to not have huge and long path as mathematically they do not bring anything of interest and just give
    // bigger numbers, which are not in the scope of this paper
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(range_min, range_max);
    std::vector<Point> points;
    points.reserve(num_points);
    for (int i = 0; i < num_points; ++i) {
        double x = dis(gen);
        double y = dis(gen);
        points.emplace_back(Point(x, y));
    }
    return points;
}

std::vector<Point> generate_skewed(int num_points, double x_min, double x_max, double y_min, double y_max) {
    std::vector<Point> points;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis_x(x_min, x_max);
    std::uniform_real_distribution<> dis_y(y_min, y_max);

    // we generate n skewed points toward the x axis. Throguht this cases of special random points we are trying to see if we can find some
    // special cases of points that give us a delaunay triangulation that affects our discretization methods
    for (int i = 0; i < num_points; ++i) {
        double x = dis_x(gen);
        double y = dis_y(gen) + 0.1 * (x - x_min);
        points.emplace_back(Point(x, y));
    }

    return points;
}
std::vector<Point> generate_clusters(int clusters, int points_per_cluster, double gap_size) {
    std::vector<Point> points;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis_cluster(0, gap_size);

    // we create clusters of points in order to disturb the triangulation, each cluster with have the same no. of points with a certain gap between them
    // again we are trying to find inputs that 'derange' the triaangualtion and affect the shortest path problem
    for (int c = 0; c < clusters; ++c) {
        double cluster_x = c * gap_size;
        double cluster_y = c * gap_size;

        for (int i = 0; i < points_per_cluster; ++i) {
            double x = cluster_x + dis_cluster(gen);
            double y = cluster_y + dis_cluster(gen);
            points.emplace_back(Point(x, y));
        }
    }
    return points;
}
std::vector<Point> generate_boundary_points(int num_points, double x_min, double x_max, double y_min, double y_max) {
    std::vector<Point> points;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis_x(x_min, x_max);
    std::uniform_real_distribution<> dis_y(y_min, y_max);

    // this is the most special of the cases as we build a rectangle and generate points alonside it's edges
    // this cases disturb the triangulation adn especially the discretization methods as it will not given reasons to go outside of the edges
    for (int i = 0; i < num_points / 4; ++i) {
        points.emplace_back(Point(dis_x(gen), y_min));
        points.emplace_back(Point(dis_x(gen), y_max));
        points.emplace_back(Point(x_min, dis_y(gen)));
        points.emplace_back(Point(x_max, dis_y(gen)));
    }

    return points;
}

void get_random_source_destination(const Delaunay& dt, Point& source, Point& destination) {
    double xmin = std::numeric_limits<double>::max();
    double ymin = std::numeric_limits<double>::max();
    double xmax = std::numeric_limits<double>::lowest();
    double ymax = std::numeric_limits<double>::lowest();

    // we first use the dt object, the CGAL::Delaunay object in order to explore it s vertices and
    // find out what is the bounding box of the triangualtion so we can properly generetae source and destination
    for (auto vertex = dt.finite_vertices_begin(); vertex != dt.finite_vertices_end(); ++vertex) {
        const Point& p = vertex->point();
        xmin = std::min(xmin, p.x());
        ymin = std::min(ymin, p.y());
        xmax = std::max(xmax, p.x());
        ymax = std::max(ymax, p.y());
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis_x(xmin, xmax);
    std::uniform_real_distribution<> dis_y(ymin, ymax);

    auto is_valid_point = [&](const Point& p) {
        auto face = dt.locate(p);
        return face != nullptr && !dt.is_infinite(face);
    };
    // we use this helper to check it the point is inside any face,
    // we keep generating points until one is inside the triangle
    // same idea for the destiantion point
    do {
        source = Point(dis_x(gen), dis_y(gen));
    } while (!is_valid_point(source));

    do {
        destination = Point(dis_x(gen), dis_y(gen));
    } while (!is_valid_point(destination));
}
void attach_point_to_graph(Graph& graph, const Point& source, const Point& destination, const std::vector<triangle_face>& faces) {
    // after generating the two points
    // we must attach them to points of the graph, first we find the face the points are in in order to later use to get
    // cost of the eddge
    auto find_triangle_for_point = [](const Point& point, const std::vector<triangle_face>& faces) -> const triangle_face* {
        for (const auto& face : faces) {
            CGAL::Triangle_2<Kernel> triangle(face.vertex[0], face.vertex[1], face.vertex[2]);
            if (triangle.bounded_side(point) == CGAL::ON_BOUNDED_SIDE) {
                return &face; // we create a CGAL::Trinagle object in ordet ro use bounded_side to see if the point is in the tringulation
            }
        }
        return nullptr;
    };

    const triangle_face* source_face = find_triangle_for_point(source, faces);
    const triangle_face* destination_face = find_triangle_for_point(destination, faces);


    if (!source_face) {
        throw std::runtime_error("Source point is not inside any triangle face.");
    }
    if (!destination_face) {
        throw std::runtime_error("Destination point is not inside any triangle face.");
    }


    // we now add the two points to the graph by searching the nearest edge to them, ennsuring the optimality of the problm
    // we do the exact same procedure for the soruce and the destination
    if (graph.vertices.find(source) == graph.vertices.end()) {
        Point nearest_source;
        double min_distance_source = std::numeric_limits<double>::max();
        for (const auto& vertex : graph.vertices) {
            double distance = source_face->weight*CGAL::to_double(CGAL::squared_distance(source, vertex));
            if (distance < min_distance_source) {
                min_distance_source = distance;
                nearest_source = vertex;
            }
        }

        graph.vertices.insert(source);
        if (!graph.vertices.empty()) {
            double weight = std::sqrt(min_distance_source) * source_face->weight;
            graph.edges.insert(Edge(source, nearest_source, weight));
        }
    }
    if (graph.vertices.find(destination) == graph.vertices.end()) {
        Point nearest_destination;
        double min_distance_destination = std::numeric_limits<double>::max();
        for (const auto& vertex : graph.vertices) {
            double distance = source_face->weight*CGAL::to_double(CGAL::squared_distance(destination, vertex));
            if (distance < min_distance_destination) {
                min_distance_destination = distance;
                nearest_destination = vertex;
            }
        }

        graph.vertices.insert(destination);
        if (!graph.vertices.empty()) {
            double weight = std::sqrt(min_distance_destination) * destination_face->weight;
            graph.edges.insert(Edge(destination, nearest_destination, weight));
        }
    }
}
