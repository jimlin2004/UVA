#include <cstdio>
#include <cmath>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge
{
    int u, v; 
    double w;
    bool operator<(const Edge& other) const
    {
        return this->w < other.w;
    }
};

struct Point
{
    double x, y;
};

vector<Edge> edges;
vector<Point> points;
int parent[105];
int n;

double calcDis(const Point& p1, const Point& p2)
{
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

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

double kurskal()
{
    double res = 0;
    int edgeNum = 0;

    sort(edges.begin(), edges.end());
    for (Edge& e: edges)
    {
        if (Union(e.u, e.v))
        {
            ++edgeNum;
            res += e.w;
            if (edgeNum == n - 1)
                return res;
        }
    }
    return res;
}

int main()
{
    int Case;
    bool flag = false;
    double x, y;
    scanf("%d", &Case);
    while (Case--)
    {
        getchar(); // for \n
        if (flag)
            puts("");
        else
            flag = true;
        
        scanf("%d", &n);
        points.clear();
        edges.clear();
        memset(parent, -1, sizeof(parent));
        for (int i = 0; i < n; ++i)
        {
            scanf("%lf %lf", &x, &y);
            points.emplace_back(Point{x, y});
        }
        //建邊
        for (int i = 0; i < points.size(); ++i)
        {
            for (int j = i + 1; j < points.size(); ++j)
            {
                double dis = calcDis(points[i], points[j]);
                edges.emplace_back(Edge{i, j, dis});
                edges.emplace_back(Edge{j, i, dis});
            }
        }

        printf("%.02lf\n", kurskal());
    }
    return 0;
}

/*
1

3
1.0 1.0
2.0 2.0
2.0 4.0
*/