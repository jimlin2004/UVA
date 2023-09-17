// floyd warshall變體

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define oo 0x3f3f3f3f

int dp[105][105];

int main()
{
    int C, S, Q;
    int u, v, w;
    bool flag = false;
    int Case = 0;
    while (scanf("%d %d %d", &C, &S, &Q) != EOF && (C + S + Q != 0))
    {
        memset(dp, 0x3f, sizeof(dp));
        if (flag)
            puts("");
        else
            flag = true;
        for (int i = 0; i < S; ++i)
        {
            scanf("%d %d %d", &u, &v, &w);
            dp[u][v] = dp[v][u] = w;
        }
        for (int k = 1; k <= C; ++k)
        {
            for (int x = 1; x <= C; ++x)
            {
                for (int y = 1; y <= C; ++y)
                {
                    dp[x][y] = min(dp[x][y], max(dp[x][k], dp[y][k]));
                }
            }
        }
        printf("Case #%d\n", ++Case);
        for (int i = 0; i < Q; ++i)
        {
            scanf("%d %d", &u, &v);
            if (dp[u][v] == oo)
                printf("no path\n");
            else
                printf("%d\n", dp[u][v]);
        }
    }
    return 0;
}