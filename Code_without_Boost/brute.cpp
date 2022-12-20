#include "brute.h"

vec2d BruteForce()
{
    int current_distance = 0, minDistance = INT_MAX;
    vec1d shortest_path;
    permute p(n);

    do
    {
        int i = 0;
        current_distance += graph[0][p.permute_list[i]];
        for (; i < n - 2; i++)
            current_distance += graph[p.permute_list[i]][p.permute_list[i + 1]];
        current_distance += graph[p.permute_list[i]][0];

        if (current_distance < minDistance)
        {
            minDistance = current_distance;
            shortest_path = p.permute_list;
            shortest_path.insert(shortest_path.begin(), 0);
        }

        current_distance = 0;
    } while (p.next_permute());

    vec2d edge_list;
    auto itr = shortest_path.begin();
    for (; itr != shortest_path.end() - 1; itr++)
    {
        vec1d temp = {*itr, *(itr + 1), graph[*itr][*(itr + 1)]};
        edge_list.push_back(temp);
    }
    vec1d temp = {*itr, shortest_path.front(), graph[*itr][shortest_path.front()]};
    edge_list.push_back(temp);

    return edge_list;
}