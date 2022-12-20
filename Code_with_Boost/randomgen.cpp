#include <iostream>
#include <math.h>
#include <time.h>
#include <vector>

#define vec1d vector<int>
#define vec2d vector<vector<int>>

using namespace std;
int distance(int a, int b)
{
    int square = pow(a, 2) + pow(b, 2);
    return pow(square, 0.5);
}
vec2d randomizer(int size)
{
    // here the current time is taken as the one to make it random
    srand(time(0));

    vec1d arrX;
    vec1d arrY;
    vec2d example;

    for (int i = 0; i < size; i++)
        arrX.push_back(rand() % 15 + 40);
    for (int i = 0; i < size; i++)
        arrY.push_back(rand() % 15 + 40);

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
    return example;
}

int main()
{
    cout << "Enter size : ";
    int size;
    cin >> size;
    vec2d example = randomizer(size);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << example[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}