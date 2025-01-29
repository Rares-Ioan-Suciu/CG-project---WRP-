# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/rares655/test_project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rares655/test_project/build

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/rares655/test_project/build/CMakeFiles /home/rares655/test_project/build//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/rares655/test_project/build/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named delaunay

# Build rule for target.
delaunay: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 delaunay
.PHONY : delaunay

# fast build rule for target.
delaunay/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/delaunay.dir/build.make CMakeFiles/delaunay.dir/build
.PHONY : delaunay/fast

Astar.o: Astar.cpp.o
.PHONY : Astar.o

# target to build an object file
Astar.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/delaunay.dir/build.make CMakeFiles/delaunay.dir/Astar.cpp.o
.PHONY : Astar.cpp.o

Astar.i: Astar.cpp.i
.PHONY : Astar.i

# target to preprocess a source file
Astar.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/delaunay.dir/build.make CMakeFiles/delaunay.dir/Astar.cpp.i
.PHONY : Astar.cpp.i

Astar.s: Astar.cpp.s
.PHONY : Astar.s

# target to generate assembly for a file
Astar.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/delaunay.dir/build.make CMakeFiles/delaunay.dir/Astar.cpp.s
.PHONY : Astar.cpp.s

delaunay_trig.o: delaunay_trig.cpp.o
.PHONY : delaunay_trig.o

# target to build an object file
delaunay_trig.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/delaunay.dir/build.make CMakeFiles/delaunay.dir/delaunay_trig.cpp.o
.PHONY : delaunay_trig.cpp.o

delaunay_trig.i: delaunay_trig.cpp.i
.PHONY : delaunay_trig.i

# target to preprocess a source file
delaunay_trig.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/delaunay.dir/build.make CMakeFiles/delaunay.dir/delaunay_trig.cpp.i
.PHONY : delaunay_trig.cpp.i

delaunay_trig.s: delaunay_trig.cpp.s
.PHONY : delaunay_trig.s

# target to generate assembly for a file
delaunay_trig.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/delaunay.dir/build.make CMakeFiles/delaunay.dir/delaunay_trig.cpp.s
.PHONY : delaunay_trig.cpp.s

dijkstra.o: dijkstra.cpp.o
.PHONY : dijkstra.o

# target to build an object file
dijkstra.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/delaunay.dir/build.make CMakeFiles/delaunay.dir/dijkstra.cpp.o
.PHONY : dijkstra.cpp.o

dijkstra.i: dijkstra.cpp.i
.PHONY : dijkstra.i

# target to preprocess a source file
dijkstra.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/delaunay.dir/build.make CMakeFiles/delaunay.dir/dijkstra.cpp.i
.PHONY : dijkstra.cpp.i

dijkstra.s: dijkstra.cpp.s
.PHONY : dijkstra.s

# target to generate assembly for a file
dijkstra.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/delaunay.dir/build.make CMakeFiles/delaunay.dir/dijkstra.cpp.s
.PHONY : dijkstra.cpp.s

discretization.o: discretization.cpp.o
.PHONY : discretization.o

# target to build an object file
discretization.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/delaunay.dir/build.make CMakeFiles/delaunay.dir/discretization.cpp.o
.PHONY : discretization.cpp.o

discretization.i: discretization.cpp.i
.PHONY : discretization.i

# target to preprocess a source file
discretization.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/delaunay.dir/build.make CMakeFiles/delaunay.dir/discretization.cpp.i
.PHONY : discretization.cpp.i

discretization.s: discretization.cpp.s
.PHONY : discretization.s

# target to generate assembly for a file
discretization.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/delaunay.dir/build.make CMakeFiles/delaunay.dir/discretization.cpp.s
.PHONY : discretization.cpp.s

experimentPart.o: experimentPart.cpp.o
.PHONY : experimentPart.o

# target to build an object file
experimentPart.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/delaunay.dir/build.make CMakeFiles/delaunay.dir/experimentPart.cpp.o
.PHONY : experimentPart.cpp.o

experimentPart.i: experimentPart.cpp.i
.PHONY : experimentPart.i

# target to preprocess a source file
experimentPart.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/delaunay.dir/build.make CMakeFiles/delaunay.dir/experimentPart.cpp.i
.PHONY : experimentPart.cpp.i

experimentPart.s: experimentPart.cpp.s
.PHONY : experimentPart.s

# target to generate assembly for a file
experimentPart.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/delaunay.dir/build.make CMakeFiles/delaunay.dir/experimentPart.cpp.s
.PHONY : experimentPart.cpp.s

main.o: main.cpp.o
.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/delaunay.dir/build.make CMakeFiles/delaunay.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i
.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/delaunay.dir/build.make CMakeFiles/delaunay.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s
.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/delaunay.dir/build.make CMakeFiles/delaunay.dir/main.cpp.s
.PHONY : main.cpp.s

read_points.o: read_points.cpp.o
.PHONY : read_points.o

# target to build an object file
read_points.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/delaunay.dir/build.make CMakeFiles/delaunay.dir/read_points.cpp.o
.PHONY : read_points.cpp.o

read_points.i: read_points.cpp.i
.PHONY : read_points.i

# target to preprocess a source file
read_points.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/delaunay.dir/build.make CMakeFiles/delaunay.dir/read_points.cpp.i
.PHONY : read_points.cpp.i

read_points.s: read_points.cpp.s
.PHONY : read_points.s

# target to generate assembly for a file
read_points.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/delaunay.dir/build.make CMakeFiles/delaunay.dir/read_points.cpp.s
.PHONY : read_points.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... delaunay"
	@echo "... Astar.o"
	@echo "... Astar.i"
	@echo "... Astar.s"
	@echo "... delaunay_trig.o"
	@echo "... delaunay_trig.i"
	@echo "... delaunay_trig.s"
	@echo "... dijkstra.o"
	@echo "... dijkstra.i"
	@echo "... dijkstra.s"
	@echo "... discretization.o"
	@echo "... discretization.i"
	@echo "... discretization.s"
	@echo "... experimentPart.o"
	@echo "... experimentPart.i"
	@echo "... experimentPart.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
	@echo "... read_points.o"
	@echo "... read_points.i"
	@echo "... read_points.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

