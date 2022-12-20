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

struct VertexProps
{
    int fontsize;
    std::string color;
    auto key() const { return std::tie(color); }
    bool operator<(const VertexProps &rhs) const { return std::tie(color) < std::tie(rhs.color); }
};
struct EdgeProps
{
    int weight;
    std::string dir = "none";
    std::string style = "invis";
    std::string color;
    std::string fontcolor;
    bool operator<(const EdgeProps &rhs) const { return std::tie(weight, dir, style, color, fontcolor) < std::tie(rhs.weight, rhs.dir, rhs.style, rhs.color, rhs.fontcolor); }
};

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
                              VertexProps, EdgeProps>
    Ugraph;

void getmatrix();
void changeStyle(Ugraph &g, int e1, int e2, const std::string style);
void changeColor(Ugraph &g, int e1, int e2, const std::string color);
void changeSC(Ugraph &g, int e1, int e2, const std::string style, const std::string color);
std::tuple<Ugraph, Ugraph> makeUgraph();
void rendergraph(Ugraph g, int currentDistance);
void edge_list_render(vec2d edge_list, std::string path, bool final);
int distance(int a, int b);
vec2d randomizer(int size);
void printEdgeList(vec2d edge_list);

#endif