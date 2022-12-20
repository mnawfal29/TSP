#ifndef brute_h
#define brute_h
#include "graph_include.h"

class permute
{
private:
    int n;
    void swap(int i, int j)
    {
        int temp = permute_list[j];
        permute_list[j] = permute_list[i];
        permute_list[i] = temp;
    }

public:
    vec1d permute_list;
    permute(int n)
    {
        this->n = n;
        for (int i = 1; i < n; i++)
            permute_list.push_back(i);
    }
    bool next_permute()
    {
        if (n == 0)
            return false;

        int i, j;
        i = j = n - 2;
        while (i > 0 && permute_list[i - 1] >= permute_list[i])
            --i;

        if (i == 0)
            return false;

        while (permute_list[j] <= permute_list[i - 1])
            --j;

        swap(i - 1, j);

        j = n - 2;
        while (i < j)
        {
            swap(i, j);
            i++;
            j--;
        }
        
        return true;
    }
};

vec2d BruteForce();

#endif