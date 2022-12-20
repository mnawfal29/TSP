// C++ implementation of the approach
#include "backtracking.h"
using namespace std;

static int backtrackingCount;
static Ugraph full, g;
vec2d GlobalSolution(n, vec1d(n, 0));
static int image_no = 0;

vec2d makeEdgeSequence(vec2d graph, vec2d arr)
{
    vec2d edgeSequence;
    int count = 0;
    int stage = 0;
    while (count < n)
    {
        for (int j = 0; j < n; j++)
        {
            if (arr[stage][j] != 0)
            {
                vec1d EdgePair;
                EdgePair.push_back(stage);
                EdgePair.push_back(j);
                EdgePair.push_back(graph[stage][j]);
                edgeSequence.push_back(EdgePair);
                stage = j;
                break;
            }
        }
        count++;
    }
    return edgeSequence;
}

void tsp(vector<bool> &v, int currPos, int count, int cost, int &ans, vec2d &DFS)
{

    if (cost > ans)
        return;
    if (count == n && graph[currPos][0])
    {
        if (ans > cost + graph[currPos][0])
        {
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    GlobalSolution[i][j] = DFS[i][j];

            GlobalSolution[currPos][0] = graph[currPos][0];
            ans = cost + graph[currPos][0];
        }
        return;
    }

    for (int i = 0; i < n; i++)
    {
        if (!v[i] && graph[currPos][i])
        {
            // Mark as visited
            v[i] = true;
            DFS[currPos][i] = graph[currPos][i];

            changeSC(g, currPos, i, emp, red);

            // Uncommenting the below lines will produce images for all the steps in backtracking. Code will take longer to execute
            // Make sure to reduce the graph size in rendergraph()[present in graph_include.cpp] so that execution doesn't take too long
            // Also uncomment system() lines in the start of Bactracking()

            // rendergraph(g, cost + graph[currPos][i]);
            // render_string << "dot -Tpng a.dot -o file.png && cp file.png ./BackTracking/" << image_no++ << ".png";
            // system(render_string.str().c_str());
            // render_string.str(string());

            tsp(v, i, count + 1, cost + graph[currPos][i], ans, DFS);

            changeSC(g, currPos, i, emp, black);

            // rendergraph(g, cost);
            // render_string << "dot -Tpng a.dot -o file.png && cp file.png ./BackTracking/" << image_no++ << ".png";
            // system(render_string.str().c_str());
            // render_string.str(string());
            DFS[currPos][i] = 0;
            // Mark ith node as unvisited
            v[i] = false;
        }
    }
};

vec2d Backtracking()
{
    // system("rm -rf BacktrackSteps");
    // system("mkdir BactrackSteps");
    backtrackingCount = 1;
    GlobalSolution.resize(n, vec1d(n, 0));
    std::tie(full, g) = makeUgraph();

    vec2d DFSGraph(n, vec1d(n, 0));

    vector<bool> v(n);
    for (int i = 0; i < n; i++)
        v[i] = false;

    v[0] = true;
    int ans = INT_MAX;

    tsp(v, 0, 1, 0, ans, DFSGraph);

    vec2d FinalEdgeSequence = makeEdgeSequence(graph, GlobalSolution);
    return FinalEdgeSequence;
}
