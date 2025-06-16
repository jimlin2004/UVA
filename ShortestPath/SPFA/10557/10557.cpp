#include <bits/stdc++.h>
using namespace std;

/*
    會贏的有兩種
    1. 有正環，且正環上可以走到終點
    2. 可以從s找到正path到t

    所以用spfa找最大路，判斷正環，預處理那些點與t連通
*/

#define maxn 105

vector<vector<int>> invG; // 反向圖
vector<vector<int>> G;
int energy[maxn];
bool reachable[maxn]; // 是否連接終點
int dis[maxn];
int cnt[maxn]; // spfa用
int inqueue[maxn]; // spfa用

void dfs(int u)
{
    reachable[u] = true;
    for (int v: invG[u])
    {
        if (!reachable[v])
        {
            dfs(v);
        }
    }
}

// 找最大路
bool spfa(int s, int t, int n)
{
    fill(dis + 1, dis + n + 1, 0);
    memset(cnt, 0, sizeof(cnt));
    memset(inqueue, 0, sizeof(inqueue));

    queue<int> q;
    q.push(s);
    inqueue[s] = true;
    dis[s] = 100;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        inqueue[u] = false;
        ++cnt[u];
        if (cnt[u] >= n && reachable[u])
            return true;

        if (dis[u] <= 0) continue; // 沒能量就不能走

        for (int v: G[u])
        {
            if (dis[v] < dis[u] + energy[v])
            {
                dis[v] = dis[u] + energy[v];
                if (!inqueue[v] && cnt[v] < n)
                {
                    q.push(v);
                    inqueue[v] = true;
                }
            }
        }
    }

    return dis[t] > 0;
}

int main()
{
    int n;
    while (scanf("%d", &n) && n != -1)
    {
        G.assign(n + 5, {});
        invG.assign(n + 5, {});

        for (int u = 1; u <= n; ++u)
        {
            scanf("%d", &energy[u]);
            int m;
            scanf("%d", &m);
            int v;
            for (int j = 0; j < m; ++j)
            {
                scanf("%d", &v);
                G[u].push_back(v);

                invG[v].push_back(u);
            }
        }

        memset(reachable, 0, sizeof(reachable));
        dfs(n);

        if (spfa(1, n, n))
            puts("winnable");
        else
            puts("hopeless");
    }

    return 0;
}