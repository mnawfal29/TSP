#ifndef branch_bound_h
#define branch_bound_h
#include "graph_include.h"
int firstMin(int i);
int secondMin(int i);
void TSPRec(int curr_bound, int curr_weight,
            int level, vec1d &curr_path);
void TSP();
vec2d Branch_And_Bound();
#endif