#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
//歐拉迴路(全是偶點)
//不能用vector<vector<int>> G去紀錄，因為有可能重邊

int n;
int G[55][55];
int degree[55];
bool hasRes;
int maxNodeIndex;

void dfs(int u)
{
    for (int v = 0; v <= maxNodeIndex; ++v)
    {
        if (G[u][v])
        {
            --G[u][v], --G[v][u];
            dfs(v);
            printf("%d %d\n", v, u); //必須逆向，否則可能出現(1, 2), (1, 3)
        }
    }
}

int main()
{
    int T;
    int u, v;
    scanf("%d", &T);
    for (int Case = 1; Case <= T; ++Case)
    {
        scanf("%d", &n);
        memset(degree, 0, sizeof(degree));
        memset(G, 0, sizeof(G));
        hasRes = true;
        maxNodeIndex = -1;
        for (int i = 0; i < n; ++i)
        {
            scanf("%d %d", &u, &v);
            ++G[u][v];
            ++G[v][u];
            ++degree[u];
            ++degree[v];
            maxNodeIndex = max(maxNodeIndex, max(u, v));
        }

        for (int i = 0; i <= maxNodeIndex; ++i)
        {
            if (degree[i] & 1)
            {
                hasRes = false;
                break;
            }
        }

        if (Case != 1)
            puts("");

        if (!hasRes)
        {
            printf("Case #%d\nsome beads may be lost\n", Case);
            continue;
        }

        printf("Case #%d\n", Case);
        dfs(u);//隨意一個點
    }
}