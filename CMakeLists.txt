cmake_minimum_required(VERSION 3.10)
project(DelaunayExample)

set(CGAL_DIR /home/rares655/cgal/CGAL-5.6.2)

find_package(CGAL REQUIRED)
find_package(Boost REQUIRED)

set(SOURCES 
    main.cpp
    discretization.cpp
    dijkstra.cpp
    read_points.cpp
    delaunay_trig.cpp
    delaunay_trig.h
    graph.h
        Astar.cpp
        Astar.h
        experimentPart.cpp
        experimentPart.h
)

add_executable(delaunay ${SOURCES})
target_link_libraries(delaunay CGAL::CGAL)
