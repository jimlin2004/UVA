#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;

#define oo 2147483647

vector<pair<int, int>> adj[1001];
int dist[1001];
bool visited[1001];
int path[1001];

void dijkstra(int src, int N)
{
    priority_queue<pair<int, int>> pq;
    for (int i = 1; i <= N; i++)
    {
        dist[i] = oo;
        visited[i] = false;
    }
    dist[src] = 0;
    pq.push({dist[src], src});
    pair<int, int> p;
    while (!pq.empty())
    {
        p = pq.top();
        pq.pop();
        if (visited[p.second])
            continue;
        visited[p.second] = true;
        for (pair<int, int> e: adj[p.second])
        {
            if (dist[p.second] + e.second < dist[e.first])
            {
                dist[e.first] = dist[p.second] + e.second;
                pq.push({-dist[e.first], e.first});
            }
        }
    }
}

int countPath(int v)
{
    if (path[v] != -1)
        return path[v];
    int ways = 0;
    for (pair<int, int> e: adj[v])
    {
        if (dist[e.first] > dist[v])
            ways += countPath(e.first);
    }
    path[v] = ways;
    return ways;
}

int main()
{
    int N, M;
    int a, b, d;
    while (scanf("%d", &N))
    {
        if (N == 0)
            break;
        scanf("%d", &M);
        for (int i = 0; i < M; i++)
        {
            scanf("%d %d %d", &a, &b, &d);
            adj[a].push_back({b, d});
            adj[b].push_back({a, d});
        }
        dijkstra(2, N);
        for (int i = 0; i <= N; i++)
            path[i] = -1;
        path[1] = 1;
        printf("%d\n", countPath(2));
        for (int i = 0; i <= N; i++)
            adj[i].clear();
    }
    return 0;
}