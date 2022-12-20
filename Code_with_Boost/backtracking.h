#ifndef backtracking_h
#define backtracking_h
#include "graph_include.h"

extern vec2d makeEdgeSequence(vec2d graph, vec2d arr);
void tsp(std::vector<bool> &v, int currPos, int count, int cost, int &ans, vec2d &DFS);
vec2d Backtracking();

#endif