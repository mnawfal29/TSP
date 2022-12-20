#include "greedy_heuristic.h"
using namespace std;

vec2d GreedyApproach()
{
    vec2d output_vector;

    // if the value == 1, we have visited the node already
    vec1d vertice_degree_vector;

    // initialise the array
    for (int j = 0; j < n; j++)
    {
        vertice_degree_vector.push_back(0);
    }

    vec2d edge_visited;
    // initialise the edge visited array
    for (int i = 0; i < n; i++)
    {
        vec1d temp;
        for (int j = 0; j < n; j++)
        {
            temp.push_back(0);
        }
        edge_visited.push_back(temp);
    }

    for (int i = 0; i < n; i++)
    {
        // we assume that the edge will be in between start_vertex and end_vertex
        int start_vertex = 0;
        int end_vertex = 0;

        // let us use the minimum distance in the adjacency apart from the connected nodes -> and add it to the output
        int min_dist_adj = INT_MAX;

        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                // checks only if the degree is less than 2 ie it should be unselected edge
                if (vertice_degree_vector[j] < 2 && vertice_degree_vector[k] < 2)
                {
                    if (i != n - 1)
                    {
                        if (vertice_degree_vector[j] == 1 && vertice_degree_vector[k] == 1)
                        {
                            int check = 0;
                            int check_vertex = j;
                            int prev_check_vertex = k;
                            while (1)
                            {
                                int flag = 0;
                                for (int z = 0; z < n; z++)
                                {
                                    if (edge_visited[z][check_vertex] == 1)
                                    {
                                        if (z != prev_check_vertex)
                                        {
                                            prev_check_vertex = check_vertex;
                                            check_vertex = z;
                                            flag = 1;
                                            break;
                                        }
                                    }
                                }
                                // if no edge is there
                                if (flag == 0)
                                {
                                    break;
                                }
                                if (check_vertex == k)
                                {
                                    check = 1;
                                    break;
                                }
                            }
                            if (check == 1)
                            {
                                continue;
                            }
                        }
                    }
                    // among all iterations it would find the non self loops which would have the minimum distance
                    if (j != k && graph[j][k] < min_dist_adj)
                    {
                        if (edge_visited[j][k] == 0)
                        {
                            min_dist_adj = graph[j][k];
                            start_vertex = j;
                            end_vertex = k;
                        }
                    }
                }
            }
        }

        // at this point after iterating, start_vertex and end_vertex would have the edge with the minimum edge from the rest of the vertices

        // we increase their degrees
        vertice_degree_vector[start_vertex] += 1;
        vertice_degree_vector[end_vertex] += 1;

        edge_visited[start_vertex][end_vertex] = 1;
        edge_visited[end_vertex][start_vertex] = 1;

        vec1d temp;
        temp.push_back(start_vertex);
        temp.push_back(end_vertex);
        temp.push_back(graph[temp[1]][temp[0]]);

        output_vector.push_back(temp);
    }

    return output_vector;
}