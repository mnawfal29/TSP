#include "graph_include.h"
#include "brute.h"
#include "nearestNeighbour.h"
#include "greedy_heuristic.h"
#include "branch_bound.h"
#include "backtracking.h"
using namespace std;

int main()
{
    getmatrix();
    vec2d edge_list;

    int op;
    cout << "0. Exit \n1. Get Matrix \n2. Brute Force \n3. Nearest Neighbour 1 \n4. Nearest Neighbour 2\n5. Nearest Best \n6. Greedy Heuristic \n7. Branch and Bound \n8. Backtracking\n"
         << endl;
    do
    {
        cout << "Enter option: ";
        scanf("%d", &op);
        cout << endl;
        if (op == 1)
        {
            cout << "Enter 0 to get default matrix or Enter size to get random matrix: ";
            cin >> n;
            cout << endl;
            getmatrix();
            continue;
        }
        else if (op == 2)
        {
            cout << "BruteForce:" << endl;
            edge_list = BruteForce();
            printEdgeList(edge_list);
        }
        else if (op == 3)
        {
            int start;
            cout << "Enter starting vertex: ";
            cin >> start;
            cout << endl;
            if (start <= n - 1)
            {
                cout << "Nearest Neighbour 1:" << endl;
                edge_list = nearestNeighbourOneWay(start);
                printEdgeList(edge_list);
            }
            else
                cout << "Start index out of bounds" << endl;
        }
        else if (op == 4)
        {
            int start;
            cout << "Enter starting vertex: ";
            cin >> start;
            cout << endl;
            if (start <= n - 1)
            {
                cout << "Nearest Neighbour 2:" << endl;
                edge_list = nearestNeighbourTwoWay(start);
                printEdgeList(edge_list);
            }
            else
                cout << "Start index out of bounds" << endl;
        }
        else if (op == 5)
        {
            cout << "Nearest Neighbour Best:" << endl;
            edge_list = nearestBest();
            printEdgeList(edge_list);
        }

        else if (op == 6)
        {
            cout << "Greedy Heuristic:" << endl;
            edge_list = GreedyApproach();
            printEdgeList(edge_list);
            printEdgeList(edge_list);
        }
        else if (op == 7)
        {
            cout << "Branch and Bound:" << endl;
            edge_list = Branch_And_Bound();
            printEdgeList(edge_list);
        }
        else if (op == 8)
        {
            cout << "Backtracking:" << endl;
            edge_list = Backtracking();
            printEdgeList(edge_list);
        }

        cout << endl;
    } while (op);
}