#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;

#define MAXNUM 50005
#define oo 0x3f3f3f3f

int dist[MAXNUM];
bool done[MAXNUM];
vector<pair<int, int>> adj[MAXNUM];

int main()
{
    int t;
    int N, M, S, T;
    int u, v, w;
    int Case = 1;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d %d %d %d", &N, &M, &S, &T);
        for (int i = 0; i <= N; ++i)
        {
            dist[i] = oo;
            done[i] = false;
            adj[i].clear();
        }
        for (int i = 0; i < M; ++i)
        {
            scanf("%d %d %d", &u, &v, &w);
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
        
        priority_queue<pair<int, int>> pq;
        dist[S] = 0;
        pq.push({dist[S], S});
        while (!pq.empty())
        {
            pair<int, int> p = pq.top();
            pq.pop();
            v = p.second;
            if (done[v]) continue;
            done[v] = true;
            for (pair<int, int>& edge: adj[v])
            {
                u = edge.first;
                w = edge.second;
                if (dist[v] + w < dist[u])
                {
                    dist[u] = dist[v] + w;
                    pq.push({-dist[u], u});
                }
            }
        }
        if (dist[T] == oo)
            printf("Case #%d: unreachable\n", Case++);
        else
            printf("Case #%d: %d\n", Case++, dist[T]);
    }
    return 0;
}