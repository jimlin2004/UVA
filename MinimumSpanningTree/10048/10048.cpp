#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge
{
    int u, v, w;
    bool operator < (const Edge& other) const
    {
        return this->w < other.w;
    }
};

int c, s, q;
int parent[105];
vector<Edge> edges;
vector<vector<Edge>> MST;

int findRoot(int x)
{
    if (parent[x] < 0)
        return x;
    return parent[x] = findRoot(parent[x]);
}

bool Union(int x, int y)
{
    int r1 = findRoot(x);
    int r2 = findRoot(y);

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

void kurskal()
{
    memset(parent, -1, sizeof(parent));
    sort(edges.begin(), edges.end());

    int edgeNum = 0;

    MST.assign(c + 5, vector<Edge>());

    for (Edge& edge: edges)
    {
        if (Union(edge.u, edge.v))
        {
            ++edgeNum;
            MST[edge.u].emplace_back(Edge{edge.u, edge.v, edge.w});
            MST[edge.v].emplace_back(Edge{edge.v, edge.u, edge.w});
            if (edgeNum == c - 1)
                break;
        }
    }
}

int dfs(int u, int p, int t, int w)
{
    int res = -1;
    for (Edge& edge: MST[u])
    {
        if (edge.v == p)
            continue;
        if (edge.v == t)
            return max(edge.w, w);
        res = max(res, dfs(edge.v, edge.u, t, max(edge.w, w)));
    }
    return res;
}

int main()
{
    int Case = 0;
    while (scanf("%d %d %d", &c, &s, &q) != EOF && (c + s + q))
    {
        int u, v, w;
        edges.clear();
        for (int i = 0; i < s; ++i)
        {
            scanf("%d %d %d", &u, &v, &w);
            edges.emplace_back(Edge{u, v, w});
            edges.emplace_back(Edge{v, u, w});
        }

        kurskal();

        if (Case != 0)
            puts("");
        printf("Case #%d\n", ++Case);

        int res;
        for (int i = 0; i < q; ++i)
        {
            scanf("%d %d", &u, &v);
            res = dfs(u, -1, v, -1);
            if (res == -1)
                printf("no path\n");
            else
                printf("%d\n", res);
        }
    }
    return 0;
}