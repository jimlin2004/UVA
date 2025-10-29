#include <bits/stdc++.h>
using namespace std;

/*
MCMF靶題
*/

#define maxn 105

struct Edge
{
    int u, v, cap, flow, cost;
};

int S, T;
vector<vector<int>> G; // 內容對應edges的index
vector<Edge> edges;
//SPFA用
bool inqueue[maxn];
int dis[maxn];
int parent[maxn];
int outFlow[maxn];

void addEdge(int u, int v, int cap, int cost)
{
    edges.emplace_back(Edge{u, v, cap, 0, cost});
    edges.emplace_back(Edge{v, u, 0, 0, -cost});
    int si = edges.size();
    G[u].emplace_back(si - 2);
    G[v].emplace_back(si - 1);
}

bool SPFA(int& maxFlow, int& minCost)
{
    memset(dis, 0x3f, sizeof(dis));
    memset(inqueue, 0, sizeof(inqueue));

    queue<int> q;
    q.push(S);
    dis[S] = 0;
    inqueue[S] = true;
    outFlow[S] = 2; // 兩個人，所以流量為2

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        inqueue[u] = false;

        for (int edgeIndex: G[u])
        {
            const Edge& edge = edges[edgeIndex];
            if ((edge.cap > edge.flow) && (dis[edge.v] > dis[edge.u] + edge.cost))
            {
                dis[edge.v] = dis[edge.u] + edge.cost;
                parent[edge.v] = edgeIndex;
                outFlow[edge.v] = min(outFlow[edge.u], edge.cap - edge.flow);
                if (!inqueue[edge.v])
                {
                    q.push(edge.v);
                    inqueue[edge.v] = true;
                }
            }
        }
    }

    // 沒路了
    if (dis[T] == 0x3f3f3f3f)
        return false;

    maxFlow += outFlow[T];
    minCost += dis[T] * outFlow[T];
    // 一路更新回去
    int curr = T;
    while (curr != S)
    {
        edges[parent[curr]].flow += outFlow[T];
        edges[parent[curr] ^ 1].flow -= outFlow[T];
        curr = edges[parent[curr]].u;
    }

    return true;
}

pair<int, int> MCMF()
{
    int maxFlow = 0;
    int minCost = 0;

    while (SPFA(maxFlow, minCost))
        ;

    return {maxFlow, minCost};
}

int main()
{
    int n, m;
    while (scanf("%d", &n) && n)
    {
        scanf("%d", &m);

        edges.clear();
        G.assign(n + 5, {});

        S = 0;
        T = n + 1;

        // 原點連1，cap = 2, cost = 0
        addEdge(S, 1, 2, 0);
        // n連終點，cap = 2, cost = 0
        addEdge(n, T, 2, 0);

        for (int i = 0; i < m; ++i)
        {
            int u, v, cost;
            scanf("%d %d %d", &u, &v, &cost);
            addEdge(u, v, 1, cost);
            addEdge(v, u, 1, cost);
        }

        pair<int, int> res = MCMF();
        int maxFlow = res.first;
        int minCost = res.second;

        if (maxFlow != 2)
            printf("Back to jail\n");
        else
            printf("%d\n", minCost);
    }

    return 0;
}

/*
2
1
1 2 999
3
3
1 3 10
2 1 20
3 2 50
9
12
1 2 10
1 3 10
1 4 10
2 5 10
3 5 10
4 5 10
5 7 10
6 7 10
7 8 10
6 9 10
7 9 10
8 9 10
0
*/