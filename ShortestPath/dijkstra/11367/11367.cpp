#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

/*
    核心概念:
    dijkstar多一個維度表示當前油量，
    對於每個點有兩種狀態要跟新
    1. 從當前點u出發到v
    2. 在當前點u加一單位的油
*/

struct Edge
{
    int u, v, w;
};

struct Item
{
    int u, remain, price;
    bool operator < (const Item& other) const
    {
        return this->price > other.price;
    }
};

int cost[1005][105]; //cost[vertex][remain油量]，很像dijkstar的dis array
bool visited[1005][105];
int prices[1005];
vector<vector<Edge>> G;

int dijkstar(int capacity, int source, int target)
{
    memset(cost, 0x3f, sizeof(cost));
    memset(visited, 0, sizeof(visited));

    priority_queue<Item> pq;
    cost[source][0] = 0;
    pq.push({source, 0, 0});

    while (!pq.empty())
    {
        Item item = pq.top();
        pq.pop();
        if (item.u == target)
            return item.price;
        if (visited[item.u][item.remain])
            continue;
        visited[item.u][item.remain] = true;

        for (Edge& edge: G[item.u])
        {
            if (edge.w > item.remain)
                continue;
            if (cost[item.u][item.remain] < cost[edge.v][item.remain - edge.w]) //由u出發到v需要耗edge.w的油量
            {
                cost[edge.v][item.remain - edge.w] = cost[item.u][item.remain];
                pq.push({edge.v, item.remain - edge.w, cost[edge.v][item.remain - edge.w]});
            }
        }
        if (item.remain < capacity && cost[item.u][item.remain] + prices[item.u] < cost[item.u][item.remain + 1])
        {
            cost[item.u][item.remain + 1] = cost[item.u][item.remain] + prices[item.u];
            pq.push({item.u, item.remain + 1, cost[item.u][item.remain + 1]});
        }
    }
    return cost[target][0];
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i)
        scanf("%d", &prices[i]);
    
    G.assign(n + 5, vector<Edge>());
    int u, v, d;
    for (int i = 0; i < m; ++i)
    {
        scanf("%d %d %d", &u, &v, &d);
        G[u].emplace_back(Edge{u, v, d});
        G[v].emplace_back(Edge{v, u, d});
    }

    int source, capacity, target;
    int q;
    scanf("%d", &q);
    while (q--)
    {
        scanf("%d %d %d", &capacity, &source, &target);
        int res = dijkstar(capacity, source, target);
        if (res == 0x3f3f3f3f)
            printf("impossible\n");
        else
            printf("%d\n", res);
    }

    return 0;
}
