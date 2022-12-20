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
        arrX.push_back(rand() % 20);
    for (int i = 0; i < size; i++)
        arrY.push_back(rand() % 20);

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
    std::cout << "\nMinimum Tour edge sequence is" << std::endl;
    for (int i = 0; i < n; i++)
    {
        std::cout << "edge:"<<edge_list[i][0] << "-" << edge_list[i][1] <<" cost:" << edge_list[i][2] << std::endl;
        pathCost += edge_list[i][2];
    }
    std::cout << "\nCost of the path is " << pathCost << std::endl;
}
