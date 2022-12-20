#include "graph_include.h"

vec2d graph;
int n;
const std::string black = "black", red = "#dc3535:#f49d1a:#dc3535", white = "white", grey = "grey", invis = "invis", emp = "", none = "none";
std::stringstream render_string;

void getmatrix()
{
    if(n)
    {
        randomizer(n);
        return;
    }
    graph.clear();
    std::ifstream f;
    f.open("matrix.txt");
    std::string line;
    while (getline(f, line))
    {
        std::istringstream lss(line);
        vec1d temp;
        int tempint;
        while (lss >> tempint)
        {
            temp.push_back(tempint);
        }
        graph.push_back(temp);
    }
    n = graph.size();
}

void changeStyle(Ugraph &g, int e1, int e2, const std::string style)
{
    g[boost::edge(e1, e2, g).first].style = style;
}

void changeColor(Ugraph &g, int e1, int e2, const std::string color)
{
    g[boost::edge(e1, e2, g).first].color = color;
    g[boost::edge(e1, e2, g).first].fontcolor = color;
}

void changeSC(Ugraph &g, int e1, int e2, const std::string style, const std::string color)
{
    g[boost::edge(e1, e2, g).first].style = style;
    g[boost::edge(e1, e2, g).first].color = color;
    g[boost::edge(e1, e2, g).first].fontcolor = color;
}

std::tuple<Ugraph, Ugraph> makeUgraph()
{
    Ugraph full(n), g(n);
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
        {
            add_edge(j, i, {graph[i][j], none, emp, black, black}, full);
            add_edge(j, i, {graph[i][j], emp, emp, grey, black}, g);
        }
    return std::make_pair(full, g);
}

void rendergraph(Ugraph g, int currentDistance)
{
    std::ofstream os("a.dot");
    std::string title;
    boost::dynamic_properties dp;
    dp.property("layout", boost::make_constant_property<Ugraph *>(std::string("circo")));
    dp.property("mindist", boost::make_constant_property<Ugraph *>(std::string("2.5")));
    dp.property("size", boost::make_constant_property<Ugraph *>(std::string("15, 15!")));
    dp.property("labelloc", boost::make_constant_property<Ugraph *>(std::string("t")));
    if (currentDistance != -1)
    {
        title = "Current Cost: " + std::to_string(currentDistance);
        dp.property("labeljust", boost::make_constant_property<Ugraph *>(std::string("r")));
    }
    else
    {
        title = "Original Graph";
        dp.property("labeljust", boost::make_constant_property<Ugraph *>(std::string("c")));
    }
    dp.property("label", boost::make_constant_property<Ugraph *>(std::string(title.c_str())));

    dp.property("node_id", boost::get(boost::vertex_index, g));
    dp.property("margin", boost::make_constant_property<Ugraph::edge_descriptor>(0.5));
    dp.property("dir", boost::get(&EdgeProps::dir, g));
    dp.property("style", boost::get(&EdgeProps::style, g));
    dp.property("headlabel", boost::get(&EdgeProps::weight, g));
    dp.property("taillabel", boost::get(&EdgeProps::weight, g));
    dp.property("color", boost::get(&EdgeProps::color, g));
    dp.property("fontcolor", boost::get(&EdgeProps::fontcolor, g));
    dp.property("penwidth", boost::make_constant_property<Ugraph::edge_descriptor>(2));
    dp.property("labeldistance", boost::make_constant_property<Ugraph::edge_descriptor>(3.5));
    dp.property("labelangle", boost::make_constant_property<Ugraph::edge_descriptor>(15));
    dp.property("fontsize", boost::make_constant_property<Ugraph::edge_descriptor>(11));
    write_graphviz_dp(os, g, dp);
}

void edge_list_render(vec2d edge_list, std::string path, bool steps)
{
    int image_no = 0;

    render_string << "rm -rf " << path;
    system(render_string.str().c_str());
    render_string.str(std::string());
    render_string << "mkdir " << path;
    system(render_string.str().c_str());
    render_string.str(std::string());

    auto [full, g] = makeUgraph();
    rendergraph(full, -1);

    render_string << "dot -Tpng a.dot -o ./" << path << "/original.png";
    system(render_string.str().c_str());
    render_string.str(std::string());

    int currentCost = 0;
    for (int j = 0; j < n; j++)
    {
        vec1d edge = edge_list[j];
        changeSC(g, edge[0], edge[1], emp, red);
        changeSC(full, edge[0], edge[1], emp, red);
        currentCost += edge[2];
        if (steps)
        {
            rendergraph(g, currentCost);
            render_string << "dot -Tpng a.dot -o ./" << path << "/" << image_no++ << ".png";
            system(render_string.str().c_str());
            render_string.str(std::string());
        }
    }

    rendergraph(full, currentCost);
    render_string << "dot -Tpng a.dot -o ./" << path << "/final.png";
    system(render_string.str().c_str());
    render_string.str(std::string());
}

int distance(int a, int b)
{
    int square = pow(a, 2) + pow(b, 2);
    return pow(square, 0.5);
}

vec2d randomizer(int size)
{
    graph.clear();
    // here the current time is taken as the one to make it random
    srand(time(0));

    vec1d arrX;
    vec1d arrY;
    vec2d example;

    for (int i = 0; i < size; i++)
        arrX.push_back(rand() % 25);
    for (int i = 0; i < size; i++)
        arrY.push_back(rand() % 25);

    bool isZero = false;
    for (int i = 0; i < size; i++)
    {
        vec1d temp;
        for (int j = 0; j < size; j++)
        {
            int dist = distance(arrX[i] - arrX[j], arrY[i] - arrY[j]);
            if (i != j && dist == 0)
            {
                isZero = true;
                break;
            }
            temp.push_back(dist);
        }
        if (isZero)
            break;
        example.push_back(temp);
    }

    // if there is zero, then we would remake the example (to avoid error)
    if (isZero)
    {
        example = randomizer(size);
    }
    graph = example;
    return example;
}

void printEdgeList(vec2d edge_list)
{
    int pathCost = 0;
    std::cout << "Minimum Tour edge sequence is" << std::endl;
    for (int i = 0; i < n; i++)
    {
        std::cout << "edge:"<<edge_list[i][0] << "-" << edge_list[i][1] <<" cost:" << edge_list[i][2] << std::endl;
        pathCost += edge_list[i][2];
    }
    std::cout << "\nCost of the path is " << pathCost << std::endl;
}