#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

/*
    <注意> 順序不用照輸入，所以先對大象sort過再做LIS，再DFS印路徑 
*/

struct Elephant
{
    int weight, IQ, ID;
    bool operator < (const Elephant& other) const
    {
        if (this->weight == other.weight)
        {
            if (this->IQ == other.IQ)
                return this->ID < other.ID;
            return this->IQ > other.IQ;
        }
        else
            return this->weight < other.weight;
    }
};

Elephant elephants[1005];
int LIS[1005];
int path[1005];

void printLIS(int u)
{
    if (u == -1)
        return ;
    printLIS(path[u]);
    printf("%d\n", elephants[u].ID + 1);
}

int main()
{
    int weight, IQ;
    int count = 0;
    while (scanf("%d %d", &weight, &IQ) != EOF)
    {
        elephants[count].weight = weight;
        elephants[count].IQ = IQ;
        elephants[count].ID = count;
        ++count;
    }

    sort(elephants, elephants + count);
    memset(path, -1, sizeof(path));

    int maxLIS = 0;
    int LISTail = -1;

    for (int i = 0; i < count; ++i)
    {
        LIS[i] = 1;
        for (int j = 0; j < i; ++j)
        {
            if (elephants[j].weight < elephants[i].weight && elephants[j].IQ > elephants[i].IQ)
            {
                if (LIS[i] < LIS[j] + 1)
                {
                    LIS[i] = LIS[j] + 1;
                    path[i] = j;
                }
            }
        }
        if (maxLIS < LIS[i])
        {
            maxLIS = LIS[i];
            LISTail = i;
        }
    }

    printf("%d\n", maxLIS);

    printLIS(LISTail);

    return 0;
}