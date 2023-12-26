#include <iostream>
#include <cstring>
using namespace std;

int M, C;
//dp[i][j] -> 買到第j - 1種時剩i元
bool dp[205][25];
int price[25][25];
//price[i][0]是第i種品項有幾個

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d %d", &M, &C);
        int n;
        for (int c = 0; c < C; ++c)
        {
            scanf("%d", &n);
            price[c][0] = n;
            for (int i = 1; i <= n; ++i)
            {
                scanf("%d", &price[c][i]);
            }
        }
        memset(dp, false, sizeof(dp));

        for (int i = 1; i <= price[0][0]; ++i)
        {
            if (M - price[0][i] >= 0)
                dp[M - price[0][i]][0] = true;
        }

        for (int j = 1; j < C; ++j)
        {
            for (int i = 0; i <= M; ++i)
            {
                if (dp[i][j - 1])
                {
                    for (int k = 1; k <= price[j][0]; ++k)
                    {
                        if (i - price[j][k] >= 0)
                            dp[i - price[j][k]][j] = true;
                    }
                }
            }
        }

        int res = -1;
        for (int i = 0; i <= M; ++i)
        {
            if (dp[i][C - 1])
            {
                res = i;
                break;
            }
        }
        if (res == -1)
            printf("no solution\n");
        else
            printf("%d\n", M - res);
    }
    return 0;
}