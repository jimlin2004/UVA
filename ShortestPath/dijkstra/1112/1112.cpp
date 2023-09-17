#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

// 核心: 所有點到終點不好做，改成終點到所有點的最短路(Dijkstar)，存圖時反過來存
const int maxN = 0x3f3f3f3f;

struct Edge
{
    int u, v, w;
};

struct Item
{
    int u, w;
    bool operator<(const Item& other) const
    {
        return this->w > other.w;
    }
};

vector<vector<Edge>> G;
bool visited[105];
int dis[105];    
int N, E, T, M;

void dijkstar()
{
    priority_queue<Item> pq;
    dis[E] = 0;
    pq.push({E, 0});
    while (!pq.empty())
    {
        Item current = pq.top();
        pq.pop();
        if (visited[current.u]) continue;
        visited[current.u] = true;
        for (Edge& e: G[current.u])
        {
            if (dis[e.v] > dis[e.u] + e.w)
            {
                dis[e.v] = dis[e.u] + e.w;
                pq.push({e.v, dis[e.v]});
            }
        }
    }
}

int main()
{
    int Case;
    int u, v, w;
    bool flag = false;
    scanf("%d", &Case);
    while (Case--)
    {
        getchar(); // for \n
        scanf("%d", &N);
        scanf("%d", &E);
        scanf("%d", &T);
        scanf("%d", &M);

        G.assign(N + 1, vector<Edge>());
        memset(visited, false, sizeof(visited));
        memset(dis, 0x3f, sizeof(dis));

        for (int i = 0; i < M; ++i)
        {
            scanf("%d %d %d", &u, &v, &w);
            G[v].emplace_back(Edge{v, u, w});
        }

        dijkstar();

        int ans = 0;
        for (int i = 1; i <= N; ++i)
        {
            if (dis[i] <= T)
                ++ans;
        }

        if (flag)
            puts("");
        else
            flag = true;
        printf("%d\n", ans);
    }
    return 0;
}

/*
1

4
2
1
8
1 2 1
1 3 1
2 1 1
2 4 1
3 1 1
3 4 1
4 2 1
4 3 1

*/