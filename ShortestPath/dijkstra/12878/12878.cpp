#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

struct Edge
{
    int u, v, w;
    bool operator < (const Edge& other) const
    {
        return this->w > other.w;
    }
};

struct Node
{
    int node, w;
    bool operator < (const Node& other) const
    {
        return this->w > other.w;
    }
};

int P, T;
int hp;
vector<vector<Edge>> G;
int disEntrance[10005];//所有點到Entrance的最短距離
int disHp[10005];//所有點到highest peak的最短距離
bool visited[10005];

void dijkstar(int source, int dis[])
{
    memset(visited, false, sizeof(visited));
    priority_queue<Node> pq;
    dis[source] = 0;
    pq.push({source, dis[source]});
    Node current;
    while (!pq.empty())
    {
        current = pq.top();
        pq.pop();
        if (visited[current.node])
            continue;
        visited[current.node] = true;
        for (Edge& edge: G[current.node])
        {
            if (dis[edge.v] > dis[current.node] + edge.w)
            {
                dis[edge.v] = dis[current.node] + edge.w;
                pq.push({edge.v, dis[edge.v]});
            }
        }
    }
}

int main()
{
    while (scanf("%d %d", &P, &T) != EOF)
    {
        int u, v, w;
        hp = P - 1;
        G.assign(P, vector<Edge>());

        for (int i = 0; i < T; ++i)
        {
            scanf("%d %d %d", &u, &v, &w);
            G[u].emplace_back(Edge{u, v, w});
            G[v].emplace_back(Edge{v, u, w});
        }
        memset(disEntrance, 0x3f, sizeof(disEntrance));
        memset(disHp, 0x3f, sizeof(disHp));
        dijkstar(0, disEntrance);
        dijkstar(hp, disHp);
        int shortestPath = disEntrance[hp];
        int res = 0;
        for (int u = 0; u < P; ++u)
        {
            for (Edge& edge: G[u])
            {
                // 以此決定邊是否在最短路徑上(路徑不唯一)
                if (disEntrance[u] + disHp[edge.v] + edge.w == shortestPath)
                    res += edge.w;
            }
        }
        printf("%d\n", res * 2);
    }
    return 0;
}
