#include <cstdio>
#include <cstring>
#include <set>
#include <algorithm>
using namespace std;

int dp[105][105];
set<int> vertexSet;
int verticesNum;

void floydWarshall()
{
    for (int k = 0; k < 105; ++k)
        for (int x = 0; x < 105; ++x)
            for (int y = 0; y < 105; ++y)
                dp[x][y] = min(dp[x][y], dp[x][k] + dp[k][y]);
}

int main()
{
    int u, v;
    int Case = 1;
    while (scanf("%d %d", &u, &v) != EOF)
    {
        if (u == 0 && v == 0)   
            break;
        memset(dp, 0x3f, sizeof(dp));
        vertexSet.clear();
        verticesNum = 0;
        for (int i = 0; i < 105; ++i)
            dp[i][i] = 0;
        vertexSet.insert(u);
        vertexSet.insert(v);
        if (u != v)
            dp[u][v] = 1;
        while (scanf("%d %d", &u, &v) != EOF)
        {
            if (u == 0 && v == 0)
                break;
            vertexSet.insert(u);
            vertexSet.insert(v);
            if (u != v)
                dp[u][v] = 1;
        }
        floydWarshall();
        int totalCost = 0;
        int pairNum = vertexSet.size() * (vertexSet.size() - 1);
        for (int u: vertexSet)
        {
            for (int v: vertexSet)
            {
                if (u == v)
                    continue;
                totalCost += dp[u][v];
            }
        }
        printf("Case %d: average length between pages = %.03lf clicks\n", Case++, ((double)totalCost) / pairNum);
    }
    return 0;
}