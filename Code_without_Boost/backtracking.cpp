// C++ implementation of the approach
#include "backtracking.h"
using namespace std;

static int backtrackingCount;
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
                // cout<<graph[stage][j]<<endl;
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

            tsp(v, i, count + 1, cost + graph[currPos][i], ans, DFS);
            
            DFS[currPos][i] = 0;
            // Mark ith node as unvisited
            v[i] = false;
        }
    }
};

vec2d Backtracking()
{
    backtrackingCount = 1;
    GlobalSolution.resize(n, vec1d(n, 0));

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
