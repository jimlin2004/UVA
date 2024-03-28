#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

/*
概念:
    考maxFlow建模
    n是人數，m是貼紙種類
    將Bob訂為Node 0
    朋友訂為 1 ~ n - 1
    貼紙訂為 n ~ n + m - 1
    再訂終點t為 Node (n + m)

    視人到貼紙的邊代表可以供交換的
    貼紙到人代表那位沒有該貼紙所以可交換的
    再將貼紙建一個到終點t的邊(cap = 1)
    <注> 
        Bob希望有最多種貼紙，所有只要他有的貼紙都可以拿去換換看
        有沒有辦法越多種越好。
        其他朋友可以與Bob交換，但擁有的貼紙至少要留一張，
        否則沒理由要跟Bob換而犧牲自己

    剩下就是maxFlow問題
    在此用Dinic
*/

struct Edge
{
    int cap = 0;
    int flow = 0;
};

//最大節點數
const int maxn = 10 + 25 + 5; 
int s, t;
int n, m;
bool visited[maxn];
Edge G[maxn][maxn];
vector<vector<int>> adj;
//stickers[i][j] -> 第i位第j種sticker的數量(第0位是Bob)
int stickers[15][30];
//BFS上與source的距離
int d[maxn];

bool bfs()
{
    memset(visited, 0, sizeof(visited));
    queue<int> q;
    q.push(s);
    d[s] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        visited[u] = true;
        for (int v: adj[u])
        {
            if (G[u][v].cap - G[u][v].flow > 0)
            {
                if (!visited[v])
                {
                    d[v] = d[u] + 1;
                    q.push(v);
                }
            }
        }
    }
    return visited[t];
}

int dfs(int u, int flow)
{
    if (u == t)
        return flow;
    int outFlow;
    int totalFlow = 0;
    for (int v: adj[u])
    {
        if ((d[v] == d[u] + 1) && (G[u][v].cap - G[u][v].flow > 0))
        {
            if ((outFlow = dfs(v, min(flow, G[u][v].cap - G[u][v].flow))) > 0)
            {
                G[u][v].flow += outFlow;
                G[v][u].flow -= outFlow;
                flow -= outFlow;
                totalFlow += outFlow;
                if (flow == 0)
                    break;
            }
        }
    }
    return totalFlow;
}

int dinic()
{
    int maxFlow = 0;
    while (bfs())
    {
        maxFlow += dfs(s, 0x3f3f3f3f);
    }
    return maxFlow;
}

int main()
{
    int CaseN;
    scanf("%d", &CaseN);
    for (int Case = 1; Case <= CaseN; ++Case)
    {
        memset(G, 0, sizeof(G));
        memset(stickers, 0, sizeof(stickers));
        memset(visited, 0, sizeof(visited));
        scanf("%d %d", &n, &m);
        s = 0;
        t = n + m;
        adj.assign(n + m + 5, vector<int>());
        for (int i = 0; i < n; ++i)
        {
            int num;
            scanf("%d", &num);
            int sticker;
            while (num--)
            {
                scanf("%d", &sticker);
                ++stickers[i][sticker];
            }
        }

        //Bob建圖(Bob可以不管有沒有剩下都拿去與別人交換，Bob只想要越多越好)
        for (int i = 1; i <= m; ++i)
        {
            if (stickers[0][i] > 0)
            {
                G[0][i + n - 1].cap = stickers[0][i];
                adj[0].emplace_back(i + n - 1);
                adj[i + n - 1].emplace_back(0);
            }
        }

        //其他人建圖(其他人要至少保留一張)
        for (int i = 1; i < n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                if (stickers[i][j] > 1)
                {
                    G[i][j + n - 1].cap = stickers[i][j] - 1;
                    adj[i].emplace_back(j + n - 1);
                    adj[j + n - 1].emplace_back(i);
                }
                if (stickers[i][j] == 0)
                {
                    G[j + n - 1][i].cap = 1;
                    adj[j + n - 1].emplace_back(i);
                    adj[i].emplace_back(j + n - 1);
                }
            }
        }

        //sticker節點與終點要有cap為1的邊
        for (int i = n; i < m + n; ++i)
        {
            G[i][t].cap = 1;
            adj[i].emplace_back(t);
            adj[t].emplace_back(i);
        }

        printf("Case #%d: %d\n", Case, dinic());
    }
    return 0;
}