#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define MAXM 25005

struct Edge
{
    unsigned int u, v, w;
    bool operator < (const Edge& other) const
    {
        return this->w < other.w;
    }
};

int disjointSet[MAXM];
vector<Edge> edges;

int find(int root)
{
    if (disjointSet[root] < 0)  return root;
    return disjointSet[root] = find(disjointSet[root]);
}

bool Union(int u, int v)
{
    int r1 = find(u);
    int r2 = find(v);
    if (r1 == r2)
        return false;
    if (r1 < r2)
    {
        disjointSet[r1] += disjointSet[r2];
        disjointSet[r2] = r1;
    }
    else
    {
        disjointSet[r2] += disjointSet[r1];
        disjointSet[r1] = r2;
    }
    return true;
}

bool kruskal()
{
    bool hadOutput = false;
    sort(edges.begin(), edges.end());
    for (Edge& edge: edges)
    {
        if (!Union(edge.u, edge.v))
        {
            if (hadOutput)
                printf(" ");
            printf("%d", edge.w);
            hadOutput = true;
        }
    }
    return hadOutput;
}

int main()
{
    int n, m;
    unsigned int u, v, w;
    while (scanf("%d %d", &n, &m) != EOF && (n || m))
    {
        fill(disjointSet, disjointSet + MAXM, -1);
        edges.clear();
        for (int i = 0; i < m; ++i)
        {
            scanf("%u %u %u", &u, &v, &w);
            edges.push_back({u, v, w});
        }
        if (!kruskal())
            printf("forest");
        puts("");
    }
    return 0;
}