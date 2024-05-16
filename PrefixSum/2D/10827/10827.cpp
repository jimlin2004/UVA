#include <cstdio>
#include <algorithm>
using namespace std;

/*
    基本就是2D prefix sum 找最大子矩形
    但這題多了矩形邊界相連的條件
    解法就只是把原矩陣再複製出三個
    擺法是原本矩形A
    變  A A
        A A
    這樣問題就回到了2D prefix sum 找最大子矩形
*/

#define maxn 160

int grid[maxn][maxn];
int prefixSum[maxn][maxn];

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                scanf("%d", &grid[i][j]);
                grid[i + n][j] = grid[i][j];
                grid[i][j + n] = grid[i][j];
                grid[i + n][j + n] = grid[i][j];
            }
        }

        for (int i = 1; i <= 2 * n; ++i)
        {
            for (int j = 1; j <= 2 * n; ++j)
            {
                prefixSum[i][j] = prefixSum[i - 1][j] + prefixSum[i][j - 1] - prefixSum[i - 1][j - 1] + grid[i][j];
            }
        }
        
        int globalMax = -0x3f3f3f3f;

        for (int y1 = 1; y1 <= n; ++y1)
        {
            for (int yLen = 0; yLen < n; ++yLen)
            {
                for (int x1 = 1; x1 <= n; ++x1)
                {
                    for (int xLen = 0; xLen < n; ++xLen)
                    {
                        int x2 = x1 + xLen;
                        int y2 = y1 + yLen;
                        globalMax = max(globalMax, prefixSum[y2][x2] - prefixSum[y2][x1 - 1] - prefixSum[y1 - 1][x2] + prefixSum[y1 - 1][x1 - 1]);
                    }
                }
            }
        }
        printf("%d\n", globalMax);
    }
    return 0;
}

/*
2
5
1 -1 0 0 -4
2 3 -2 -3 2
4 1 -1 5 0
3 -2 1 -3 2
-3 2 4 1 -4
3
1 2 3
4 5 6
7 8 9
*/