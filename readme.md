# Travelling Salesman Problem

How to Compile and Run:
Compile: g++ main.cpp graph_include.cpp brute.cpp greedy_heuristic.cpp branch_bound.cpp nearestNeighbour.cpp backtracking.cpp -o app
Run: ./app

For linux install:
1. Boost - sudo apt-get install libboost-all-dev
2. Graphviz - sudo apt install graphviz

Folder directory:
1. Code_with_Boost(For images) - Use with linux and above packages installed
2. Code_without_Boost - Use with linux or windows
3. Images - Contains images for current default matrix in matrix.txt

Files inside both Directories:
app - precompiled app for linux only
a.dot - Contains graphviz code
main.cpp - The main program code
graph_include.app - Contains all the necessary functions for rendering the graph and other helper functions and definitions
matrix.txt - Contains the default matrix. Can be changed depending on use case
matrix_examples - Contains some examples. Not used for running the code.
randomgen.cpp - Generates random matrices

NOTE:
To change resolution/size of final image change the size parameter in rendergraph[present in graph_include.h] from 15, 15! to required size. Don't forget the !

To get intermediate images for backtracking uncomment the lines in backtracking.cpp
