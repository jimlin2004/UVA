#include <bits/stdc++.h>
using namespace std;

// 找最小生成樹裡第s大的權重即為答案

#define maxn 505

struct Edge
{
    int u, v;
    double w;
};

struct Point
{
    double x, y;
};

Point points[maxn];
vector<Edge> edges;
int parent[maxn];

double getDis(Point& a, Point& b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int findRoot(int x)
{
    if (parent[x] < 0)
        return x;
    return parent[x] = findRoot(parent[x]);
}

bool Uni(int a, int b)
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

double kruskal(int n, int s)
{
    memset(parent, -1, sizeof(parent));
    sort(edges.begin(), edges.end(), [](Edge& a, Edge& b) {
        return a.w < b.w;
    });

    int cnt = 0;
    for (Edge& edge: edges)
    {
        if (Uni(edge.u, edge.v))
        {
            ++cnt;
            if (cnt == (n - s))
            {
                return edge.w;
            }
        }
    }

    return -1;
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int s, n;
        scanf("%d %d", &s, &n);

        for (int i = 0; i < n; ++i)
            scanf("%lf %lf", &points[i].x, &points[i].y);
    
        edges.clear();
        for (int i = 0; i < n; ++i)
        {
            for (int j = i + 1; j < n; ++j)
            {
                edges.push_back({i, j, getDis(points[i], points[j])});
            }
        }

        printf("%.2lf\n", kruskal(n, s));
    }

    return 0;
}