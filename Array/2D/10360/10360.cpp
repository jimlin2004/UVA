#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

/*
    做法就是模擬
    先建立題目的2D陣列

    然後以每個老鼠當作炸彈範圍的矩形中心(炸彈半徑是d)
    把該老鼠的數量加到一開始的2D陣列

    如此最後2D陣列的就代表如果炸彈炸在那一格總共炸到的老鼠數量

    所以要做的就只剩下遍歷一遍2D陣列找最大值輸出即可AC
*/

#define maxn 1030

int grid[maxn][maxn];

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        memset(grid, 0, sizeof(grid));
        int d;
        scanf("%d", &d);
        int n;
        scanf("%d", &n);
        int x, y, p;

        int xmin = 0x3f3f3f3f, xmax = -0x3f3f3f3f;
        int ymin = 0x3f3f3f3f, ymax = -0x3f3f3f3f;

        for (int i = 0 ;i < n; ++i)
        {
            scanf("%d %d %d", &x, &y, &p);
            xmin = min(xmin, x - d);
            xmax = max(xmax, x + d);
            ymin = min(ymin, y - d);
            ymax = max(ymax, y + d);

            for (int i = max(y - d, 0); i <= min(y + d, 1024); ++i)
            {
                for (int j = max(x - d, 0); j <= min(x + d, 1024); ++j)
                {
                    grid[i][j] += p;
                }
            }
        }
        int resX, resY, res = -0x3f3f3f3f;
        
        for (int j = max(0, xmin); j <= min(xmax, 1024); ++j)
        {
            for (int i = max(0, ymin); i <= min(ymax, 1024); ++i)
            {
                if (res < grid[i][j])
                {
                    res = grid[i][j];
                    resX = j;
                    resY = i;
                }
            }
        }
        printf("%d %d %d\n", resX, resY, res);
    }
    return 0;
}