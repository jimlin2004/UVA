#include <stdio.h>
#include <queue>
#include <string.h>
#include <vector>
using namespace std;

#define MAXN 2005
#define oo 0x3f3f3f3f

struct Edge
{
    int v, w;
};

int N, M;
vector<Edge> adj[MAXN];

bool SPFA(int s)
{
    int cnt[MAXN] = {0};
    int dist[MAXN];
    bool inqueue[MAXN] = {false};
    queue<int> q;
    
    memset(dist, oo, sizeof(dist));

    q.push(s);
    dist[s] = 0;
    inqueue[s] = true;
    cnt[s] = 1;

    int current;
    while (!q.empty())
    {
        current = q.front();
        q.pop();
        inqueue[current] = false;
        for (Edge& edge: adj[current])
        {
            if (dist[edge.v] > dist[current] + edge.w)
            {
                dist[edge.v] = dist[current] + edge.w;
                if (!inqueue[edge.v])
                {
                    if (++cnt[edge.v] >= N) return false;
                    q.push(edge.v);
                    inqueue[edge.v] = true;
                }
            }
        }
    }
    return true;
}

int main()
{
    int t;
    int u, v, w;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d %d", &N, &M);
        for (int i = 0; i <= N; ++i)
            adj[i].clear();
        for (int i = 0; i < M; ++i)
        {
            scanf("%d %d %d", &u, &v, &w);

            adj[u].push_back({v, w});
        }

        if (!SPFA(0))
            printf("possible\n");
        else
            printf("not possible\n");
    }
}