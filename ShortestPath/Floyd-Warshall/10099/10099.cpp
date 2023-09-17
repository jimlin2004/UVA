//Floyd-Warshall多源最短路徑

#include <iostream>
#include <string.h>

#define MAXN 105

int N, M;
int dp[MAXN][MAXN];

int main()
{
    int Case = 1;
    int u, v, w;
    int start, end, people;
    int ans;
    while (scanf("%d %d", &N, &M) != EOF && (N && M))
    {
        memset(dp, 0, sizeof(dp));
        //希望載客量最大，所以初始值為0
        for (int i = 0; i < M; ++i)
        {
            scanf("%d %d %d", &u, &v, &w);
            dp[u][v] = w;
            dp[v][u] = w;
        }
        for (int k = 1; k <= N; ++k)
        {
            for (int i = 1; i <= N; ++i)
            {
                for (int j = 1; j <= N; ++j)
                {
                    dp[i][j] = std::max(dp[i][j], std::min(dp[i][k], dp[k][j]));
                }
            }
        }

        scanf("%d %d %d", &start, &end, &people);
        ans = (people) / (dp[start][end] - 1); // -1 給導遊
        if (people % (dp[start][end] - 1) > 0) // 不能整除->載不完多一趟
            ++ans;
        printf("Scenario #%d\n", Case++);
        printf("Minimum Number of Trips = %d\n\n", ans);
    }
}