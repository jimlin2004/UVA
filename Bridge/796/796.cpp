#include <bits/stdc++.h>
using namespace std;

/*
    找Bridge的模板題
    low[v] > dfn[u] -> 橋
*/

vector<vector<int>> G;
vector<int> dfn;
vector<int> low;
int visTime;

vector<pair<int, int>> bridges;

void tarjan(int u, int p)
{
    dfn[u] = low[u] = visTime++;

    for (int v: G[u])
    {
        if (v == p)
            continue;
        
        if (dfn[v] == -1) // forward edge
        {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);

            if (low[v] > dfn[u]) // 從v繞不回u
                bridges.push_back({min(u, v), max(u, v)});
        }
        else // backward edge
            low[u] = min(low[u], dfn[v]);
    }
}

int main()
{
    int n;
    while (scanf("%d", &n) != EOF)
    {
        G.assign(n + 5, {});

        int u, m;
        for (int i = 0; i < n; ++i)
        {
            scanf("%d (%d)", &u, &m);
            int v;
            for (int j = 0; j < m; ++j)
            {
                scanf("%d", &v);
                G[u].push_back(v);
                G[v].push_back(u);
            }
        }

        bridges.clear();
        dfn.assign(n + 5, -1);
        low.assign(n + 5, -1);
        visTime = 0;

        for (int u = 0; u < n; ++u)
        {
            if (dfn[u] == -1)
            {
                tarjan(u, -1);
            }
        }

        sort(bridges.begin(), bridges.end());

        printf("%d critical links\n", bridges.size());
        for (auto& bridge: bridges)
            printf("%d - %d\n", bridge.first, bridge.second);
        puts("");
    }

    return 0;
}