# cmake_minimum_required(VERSION 3.14)
project(projects)

set(CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
add_executable(cmake_testapp contest/cellnetwork.cpp)
#contest/square.cpp NOT WORKING, MAYBE DUE TO BAD INITIAL CONSTRUCTION (point of sequare on known x/y axis)
#contest/replicationBFS.cpp
#Notes/data_structures/BIT/FixedPointRemoval.cpp
#usaco/gathering.cpp
#usaco/sprinklers.cpp
#usaco/exercise.cpp
#usaco/delegation.cpp
#usaco/threesum.cpp
#usaco/boards.cpp
#Notes/data_structures/treap/implicittreap.cpp
#usaco/mincross.cpp
#usaco/tallbarn.cpp
#usaco/roboherd.cpp
#usaco/team.cpp
#usaco/triangles.cpp
#usaco/262144.cpp
#usaco/cbarn.cpp
#usaco/balancingplat.cpp
#usaco/mowing2DBIT.cpp
#usaco/highlowcard.cpp