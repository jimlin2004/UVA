#include <bits/stdc++.h>
using namespace std;

/*
    不走回頭路
    dis[]是與終點的距離
    只有當dis[a] > dis[b]時才會能夠從a走到b
    所以用dijkstra得到dis
    圖會變成DAG
    就可以用DAG DP求答案
*/

#define maxn 1005

struct Edge
{
    int u, v;
    int w;
};

struct Item
{
    int u;
    int w;
    bool operator < (const Item& other) const
    {
        return w > other.w;
    }
};

vector<vector<Edge>> G;
int dis[maxn];
bool done[maxn];
int dp[maxn];

void dijkstra(int s)
{
    memset(dis, 0x3f, sizeof(dis));
    memset(done, 0, sizeof(done));

    dis[s] = 0;
    priority_queue<Item> pq;
    pq.push({s, dis[s]});

    while (!pq.empty())
    {
        Item curr = pq.top();
        pq.pop();

        if (done[curr.u])
            continue;
        done[curr.u] = true;

        for (Edge& edge: G[curr.u])
        {
            if (done[edge.v])
                continue;

            if (dis[edge.v] > dis[curr.u] + edge.w)
            {
                dis[edge.v] = dis[curr.u] + edge.w;
                pq.push({edge.v, dis[edge.v]});
            }
        }
    }
}

// 由於題目能走A -> B只有當dis[A] > dis[B]
// 所以圖會變成DAG
// 可以DP求走法
int dfs(int u)
{
    if (dp[u] != -1)
        return dp[u];
    int res = 0;
    for (Edge& edge: G[u])
    {
        if (dis[u] > dis[edge.v])
            res += dfs(edge.v);
    }

    return dp[u] = res;
}

int main()
{
    int n, m;
    while (scanf("%d", &n) && n)
    {
        G.assign(maxn, {});

        scanf("%d", &m);

        int u, v, w;
        for (int i = 0; i < m; ++i)
        {
            scanf("%d %d %d", &u, &v, &w);
            G[u].push_back({u, v, w});
            G[v].push_back({v, u, w});
        }

        dijkstra(2); // home固定是2

        memset(dp, -1, sizeof(dp));
        dp[2] = 1;

        printf("%d\n", dfs(1));
    }
    return 0;
}