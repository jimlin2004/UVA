//最小生成樹

#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;

#define MAXNUM 1000005

struct Edge
{
    int from, to, w;
    bool operator < (const Edge& other) const
    {
        return w < other.w;
    }
};

int disjointSet[MAXNUM];
int total; // 最小生成樹總和
int n;
int k, m;
vector<Edge> edge;

int find(int x)
{
    if (disjointSet[x] < 0)
        return x;
    return disjointSet[x] = find(disjointSet[x]);
}

void Union(int u, int v)
{
    int root1 = find(u);
    int root2 = find(v);
    if (root1 == root2)
        return;
    if (disjointSet[root1] <= disjointSet[root2])
    {
        disjointSet[root1] = disjointSet[root1] + disjointSet[root2];
        disjointSet[root2] = root1;
    }
    else if (disjointSet[root1] > disjointSet[root2])
    {
        disjointSet[root2] = disjointSet[root1] + disjointSet[root2];
        disjointSet[root1] = root2;
    }
}

void kruskal()
{
    memset(disjointSet, -1, sizeof(disjointSet));
    sort(edge.begin(), edge.end());
    int i, j;
    for (i = 0, j = 0;(i < n - 1 && j < m); ++i)
    {
        while (find(edge[j].from) == find(edge[j].to))
            ++j;
        Union(edge[j].from, edge[j].to);
        total += edge[j].w;
        ++j;
    }
}

int main()
{
    int originCost;
    int from, to, cost;
    bool first = false;
    while (scanf("%d", &n) != EOF)
    {
        originCost = 0;
        total = 0;
        edge.clear();
        for (int i = 0; i < n - 1; ++i)
        {
            scanf("%d %d %d", &from, &to, &cost);
            originCost += cost;
        }
        scanf("%d", &k);
        for (int i = 0; i < k; ++i)
        {
            scanf("%d %d %d", &from, &to, &cost);
            edge.push_back({from, to, cost});
        }
        scanf("%d", &m);
        for (int i = 0; i < m; ++i)
        {
            scanf("%d %d %d", &from, &to, &cost);
            edge.push_back({from, to, cost});
        }
        m += k;
        kruskal();
        if (first)
            printf("\n");
        first = true;
        printf("%d\n", originCost);
        printf("%d\n", total);
    }
    return 0;
}