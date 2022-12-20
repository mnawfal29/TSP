#include "nearestNeighbour.h"
using namespace std;

vec2d nearestNeighbourOneWay(int start)
{
	vec2d output;

	vec1d visited_nodes; // if visited the node, then the value =1, else it is 0

	// initialise the array
	for (int j = 0; j < n; j++)
	{
		visited_nodes.push_back(0);
	}

	visited_nodes[start] = 1;

	int j = 0;

	int startVertex = start;

	int min1 = INT_MAX;

	int nextnode;

	while (j < n)
	{

		// goes through all unvisited nodes from the i and finds the min
		if (j != startVertex && visited_nodes[j] == 0)
		{
			if (graph[startVertex][j] < min1)
			{
				min1 = graph[startVertex][j];
				nextnode = j;
			}
		}

		// in this manner would traverse and check all the possible paths originating from the node i
		j++;

		// at the end of the array (ie when all possible paths from the vertex is considered and route is found)
		if (j == n)
		{
			// find the minimum

			vec1d temp;
			temp.push_back(startVertex);
			temp.push_back(nextnode);
			temp.push_back(graph[temp[1]][temp[0]]);

			output.push_back(temp);

			visited_nodes[nextnode] = 1;
			startVertex = nextnode;

			// reset
			j = 0;
			min1 = INT_MAX;

			if (output.size() == n - 1)
				break;
		}
	}

	// would find a path from 0,0 which would cover each and every element (since it is a complete graph)
	vec1d temp;

	temp.push_back(startVertex);
	temp.push_back(start);
	temp.push_back(graph[temp[1]][temp[0]]);

	output.push_back(temp);

	return output;
}

vec2d nearestNeighbourTwoWay(int start)
{

	vec2d output;

	// if the value == 1, we have visited the node already
	int visited_nodes[n];

	// initialise the array
	for (int j = 0; j < n; j++)
	{
		visited_nodes[j] = 0;
	}

	// find the minimum distance in the adjacency matrix, and we will use one of the vertices as the starting index

	visited_nodes[start] = 1;

	int j = 0;

	int startVertex = start;
	int endVertex = start;

	int min1 = INT_MAX;
	int min2 = INT_MAX;

	int nextnode1;
	int nextnode2;

	while (j < n)
	{

		// goes through all unvisited nodes from the i and finds the min
		if (j != startVertex && visited_nodes[j] == 0)
		{
			if (graph[startVertex][j] < min1)
			{
				min1 = graph[startVertex][j];
				nextnode1 = j;
			}
		}
		if (j != endVertex && visited_nodes[j] == 0)
		{
			if (graph[endVertex][j] < min2)
			{
				min2 = graph[endVertex][j];
				nextnode2 = j;
			}
		}
		// in this manner would traverse and check all the possible paths originating from the node i
		j++;

		// at the end of the array (ie when all possible paths from the vertex is considered and route is found)
		if (j == n)
		{
			// printf("%d %d",startVertex, endVertex);
			// find the minimum
			if (min1 < min2)
			{

				vec1d temp;
				temp.push_back(startVertex);
				temp.push_back(nextnode1);
				temp.push_back(graph[temp[1]][temp[0]]);

				output.push_back(temp);

				visited_nodes[nextnode1] = 1;
				startVertex = nextnode1;
			}
			else
			{
				vec1d temp;

				temp.push_back(endVertex);
				temp.push_back(nextnode2);
				temp.push_back(graph[temp[1]][temp[0]]);

				output.push_back(temp);

				visited_nodes[nextnode2] = 1;
				endVertex = nextnode2;
			}
			// reset
			j = 0;
			min1 = INT_MAX;
			min2 = INT_MAX;

			if (output.size() == n - 1)
				break;
		}
	}

	// would find a path from 0,0 which would cover each and every element (since it is a complete graph)
	vec1d temp;

	temp.push_back(endVertex);
	temp.push_back(startVertex);
	temp.push_back(graph[temp[1]][temp[0]]);
	output.push_back(temp);
	return output;
}

vec2d nearestBest()
{
	int bestCost = INT_MAX;
	vec2d curr_list, output;
	for (int i = 0; i < n; i++)
	{
		curr_list = nearestNeighbourTwoWay(i);
		int pathCost = 0;
		for (int j = 0; j < n; j++)
			pathCost += curr_list[j][2];
		if(pathCost < bestCost)
		{
			output = curr_list;
			bestCost = pathCost;
		}
	}
	return output;
}