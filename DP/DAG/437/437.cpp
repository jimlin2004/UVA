#include <bits/stdc++.h>
using namespace std;

/*
    用方塊轉成DAG，做DAG DP找最大權重路徑
*/

struct Block
{
    int x, y, z;
};

struct Edge
{
    int u, v, w;
};

vector<Block> blocks;
vector<vector<Edge>> G;
int dp[200]; // 最多約30 * 6個點
int m; // 幾個點

int dfs(int u)
{
    if (dp[u] != -1)
        return dp[u];

    dp[u] = 0;
    for (Edge& edge: G[u])
    {
        dp[u] = max(dp[u], dfs(edge.v) + edge.w);
    }

    return dp[u];
}

int main()
{
    int tc = 0;

    int n;
    while (scanf("%d", &n) && n)
    {
        memset(dp, -1, sizeof(dp));
        blocks.clear();

        // 放一個無限大的，但高度為0的方塊當底
        blocks.emplace_back(Block{0x3f3f3f3f, 0x3f3f3f3f, 0});

        for (int i = 0; i < n; ++i)
        {
            int x, y, z;
            scanf("%d %d %d", &x, &y, &z);

            blocks.emplace_back(Block{x, y, z});
            blocks.emplace_back(Block{y, x, z});
            blocks.emplace_back(Block{x, z, y});
            blocks.emplace_back(Block{z, x, y});
            blocks.emplace_back(Block{y, z, x});
            blocks.emplace_back(Block{z, y, x});
        }

        m = blocks.size();
        G.assign(m + 5, {});
        // 建邊
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                if (i == j)
                    continue;
                // j可以接在i上
                if (blocks[i].x > blocks[j].x && blocks[i].y > blocks[j].y)
                {
                    G[i].emplace_back(Edge{i, j, blocks[j].z});
                }
            }
        }

        printf("Case %d: maximum height = %d\n", ++tc, dfs(0));
    }
    return 0;
}