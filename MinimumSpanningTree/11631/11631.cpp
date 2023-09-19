#include <cstring>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge
{
    int u, v, w;
    bool operator < (const Edge& edge) const
    {
        return this->w < edge.w;
    }
};

int parent[200005];
int vertexNum;
vector<Edge> edges;

int findRoot(int x)
{
    if (parent[x] < 0)
        return x;
    return parent[x] = findRoot(parent[x]);
}

bool Union(int a, int b)
{
    int r1 = findRoot(a);
    int r2 = findRoot(b);

    if (r1 == r2)
        return false;
    if (parent[r1] < parent[r2])
    {
        parent[r1] += parent[r2];
        parent[r2] = r1;
    }
    else
    {
        parent[r2] += parent[r1];
        parent[r1] = r2;
    }
    return true;
}

int kurskal()
{
    int edgeNum = 0;
    int res = 0;
    sort(edges.begin(), edges.end());

    for (Edge& edge: edges)
    {
        if (Union(edge.u, edge.v))
        {
            res += edge.w;
            ++edgeNum;
            if (edgeNum == vertexNum - 1)
                break;
        }
    }
    return res;
}

int main()
{
    int n;
    int u, v, w;
    while (scanf("%d %d", &vertexNum, &n) != EOF)
    {
        if (vertexNum == 0 && n == 0)
            break;
        memset(parent, -1, sizeof(parent));
        edges.clear();
        int totalCost = 0;
        for (int i = 0; i < n; ++i)
        {
            scanf("%d %d %d", &u, &v, &w);
            totalCost += w;
            edges.emplace_back(Edge{u, v, w});
        }

        printf("%d\n", totalCost - kurskal());
    }
    return 0;
}