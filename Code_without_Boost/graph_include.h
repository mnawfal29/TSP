#ifndef graph_include_h
#define graph_include_h

#include <bits/stdc++.h>
#include <boost/graph/graphviz.hpp>

using vec1d = std::vector<int>;
using vec2d = std::vector<vec1d>;

extern vec2d graph;
extern int n;
extern const std::string black, red, grey, white, invis, emp, none;
extern std::stringstream render_string;

void getmatrix();
void printEdgeList(vec2d edge_list);
int distance(int a, int b);
vec2d randomizer(int size);

#endif