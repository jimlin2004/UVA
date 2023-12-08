#include <cstdio>
#include <algorithm>
using namespace std;

long long grid[15][105];
int path[15][105];
int r, c;

void printPath(int i, int j)
{
    if (j == c)
    {
        printf("%d", i);
        return;
    }
        
    printf("%d ", i);
    printPath(path[i][j], j + 1);
}

int main()
{
    while (scanf("%d %d", &r, &c) != EOF)
    {
        for (int i = 1; i <= r; ++i)
        {
            for (int j = 1; j <= c; ++j)
            {
                scanf("%lld", &grid[i][j]);
            }
        }

        int r1, r2, r3;
        long long cost1, cost2, cost3;
        //為了保證字典序最小，必須要由右至左
        for (int j = c - 1; j >= 1; --j)
        {
            for (int i = 1; i <= r; ++i)
            {
                r1 = i - 1;
                if (r1 == 0)
                    r1 = r;
                r2 = i;
                r3 = i + 1;
                if (r3 == r + 1)
                    r3 = 1;
                cost1 = grid[i][j] + grid[r1][j + 1];
                cost2 = grid[i][j] + grid[r2][j + 1];
                cost3 = grid[i][j] + grid[r3][j + 1];
                path[i][j] = 0x3f3f3f3f;

                //path要字典序最小
                if (cost1 <= cost2 && cost1 <= cost3)
                {
                    grid[i][j] = cost1;
                    path[i][j] = min(path[i][j], r1);
                }
                if (cost2 <= cost1 && cost2 <= cost3)
                {
                    grid[i][j] = cost2;
                    path[i][j] = min(path[i][j], r2);
                }
                if (cost3 <= cost1 && cost3 <= cost2)
                {
                    grid[i][j] = cost3;
                    path[i][j] = min(path[i][j], r3);
                }
            }
        }

        long long minCost = 0x3f3f3f3f;
        int minR = 0;

        for (int i = 1; i <= r; ++i)
        {
            if (grid[i][1] < minCost)
            {
                minCost = grid[i][1];
                minR = i;
            }
        }

        printPath(minR, 1);

        printf("\n%lld\n", minCost);
    }
    return 0;
}