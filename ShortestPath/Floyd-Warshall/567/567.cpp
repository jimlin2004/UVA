#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

//純Floyd-Warshall

#define MaxNodeNum 25

int dp[MaxNodeNum][MaxNodeNum];

int main()
{
    int Case = 0;

    int num;
    while (scanf("%d", &num) != EOF)
    {
        memset(dp, 0x3f, sizeof(dp));
        int v;
        for (int i = 0; i < num; ++i)
        {
            scanf("%d", &v);
            dp[1][v] = 1;
            dp[v][1] = 1;
        }
        for (int u = 2; u <= 19; ++u)
        {
            scanf("%d", &num);
            for (int i = 0; i < num; ++i)
            {
                scanf("%d", &v);
                dp[u][v] = 1;
                dp[v][u] = 1;
            }
        }

        for (int k = 1; k < MaxNodeNum; ++k)
        {
            for (int x = 1; x < MaxNodeNum; ++x)
            {
                for (int y = 1; y < MaxNodeNum; ++y)
                {
                    dp[x][y] = min(dp[x][y], dp[x][k] + dp[k][y]);
                }
            }
        }

        printf("Test Set #%d\n", ++Case);

        int N;
        scanf("%d", &N);
        for (int i = 0; i < N; ++i)
        {
            int x, y;
            scanf("%d %d", &x, &y);
            printf("%2d to %2d: %d\n", x, y, dp[x][y]);
        }
        puts("");
    }
    return 0;
}