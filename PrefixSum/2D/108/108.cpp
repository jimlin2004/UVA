#include <cstdio>
#include <cstring>
#include <climits>
#include <algorithm>
using namespace std;

#define MAXN 105

int sum[MAXN][MAXN] = {0}; // sum[i][j]代表(0, 0)到(i, j)的矩形和
int nums[MAXN][MAXN] = {0}; //原數據

int main()
{
    int N;
    while (scanf("%d", &N) != EOF)
    {
        for (int i = 1; i <= N; ++i)
        {
            for (int j = 1; j <= N; ++j)
            {
                scanf("%d", &nums[i][j]);
                sum[i][j] = sum[i][j - 1] + sum[i - 1][j] - sum[i - 1][j - 1] + nums[i][j];
            }
        }

        int maxSum = INT_MIN;
        int subtotal;
        //(x1, y1) 左上角，(x2, y2)右下角
        for (int y1 = 1; y1 <= N; ++y1)
        {
            for (int x1 = 1; x1 <= N; ++x1)
            {
                for (int y2 = y1; y2 <= N; ++y2)
                {
                    for (int x2 = x1; x2 <= N; ++x2)
                    {
                        subtotal = sum[y2][x2] - sum[y1 - 1][x2] - sum[y2][x1 - 1] + sum[y1 - 1][x1 - 1];
                        maxSum = max(maxSum, subtotal);
                    }
                }
            }
        }

        printf("%d\n", maxSum);
    }
    return 0;
}