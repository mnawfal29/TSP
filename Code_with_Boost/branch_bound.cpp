#include "branch_bound.h"
using namespace std;

static vec1d final_path;
static vector<bool> visited;
int final_res = INT_MAX;

int firstMin(int i)
{
	int min = INT_MAX;
	for (int k = 0; k < n; k++)
		if (graph[i][k] < min && i != k)
			min = graph[i][k];
	return min;
}

int secondMin(int i)
{
	int first = INT_MAX, second = INT_MAX;
	for (int j = 0; j < n; j++)
	{
		if (i == j)
			continue;

		if (graph[i][j] <= first)
		{
			second = first;
			first = graph[i][j];
		}
		else if (graph[i][j] <= second &&
				 graph[i][j] != first)
			second = graph[i][j];
	}
	return second;
}

void TSPRec(int curr_bound, int curr_weight, int level, vec1d &curr_path)
{

	if (level == n)
	{
		if (graph[curr_path[level - 1]][curr_path[0]] != 0)
		{
			int curr_res = curr_weight +
						   graph[curr_path[level - 1]][curr_path[0]];

			if (curr_res < final_res)
			{
				final_path = curr_path;
				final_res = curr_res;
			}
		}
		return;
	}

	for (int i = 0; i < n; i++)
	{

		if (graph[curr_path[level - 1]][i] != 0 &&
			visited[i] == false)
		{
			int temp = curr_bound;
			curr_weight += graph[curr_path[level - 1]][i];

			if (level == 1)
				curr_bound -= ((firstMin(curr_path[level - 1]) +
								firstMin(i)) /
							   2);
			else
				curr_bound -= ((secondMin(curr_path[level - 1]) +
								firstMin(i)) /
							   2);

			if (curr_bound + curr_weight < final_res)
			{
				curr_path[level] = i;
				visited[i] = true;

				TSPRec(curr_bound, curr_weight, level + 1,
					   curr_path);
			}

			curr_weight -= graph[curr_path[level - 1]][i];
			curr_bound = temp;
			fill(visited.begin(), visited.end(), 0);
			for (int j = 0; j <= level - 1; j++)
				visited[curr_path[j]] = true;
		}
	}
}

void TSP()
{
	vec1d curr_path(n, 0);
	int curr_bound = 0;
	for (int i = 0; i < n; i++)
		curr_bound += (firstMin(i) +
					   secondMin(i));

	curr_bound = (curr_bound & 1) ? curr_bound / 2 + 1 : curr_bound / 2;

	visited[0] = true;
	curr_path[0] = 0;

	TSPRec(curr_bound, 0, 1, curr_path);
}

vec2d Branch_And_Bound()
{
	visited.resize(n, false);
	TSP();

	vec2d edge_list;
	int i;

	for (i = 0; i < n - 1; i++)
	{
		vec1d temp = {final_path[i], final_path[i + 1], graph[final_path[i]][final_path[i + 1]]};
		edge_list.push_back(temp);
	}
	vec1d temp = {final_path[0], final_path[i], graph[final_path[0]][final_path[i]]};
	edge_list.push_back(temp);
	return edge_list;
}