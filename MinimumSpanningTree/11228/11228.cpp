#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

#define MAXN 1005

struct Edge
{
    int u, v;
    double w;
    bool operator < (const Edge& other)
    {
        return this->w < other.w;
    }
};

struct City
{
    int x, y;
};

int disjointSet[MAXN];
City cities[MAXN];
vector<Edge> edges;

int rfind(int root)
{
    if (disjointSet[root] < 0)
        return root;
    return disjointSet[root] = rfind(disjointSet[root]);
}

bool Union(int r1, int r2)
{
    int p1 = rfind(r1);
    int p2 = rfind(r2);
    if (p1 == p2)
        return false;
    if (disjointSet[p1] < disjointSet[p2])
    {
        disjointSet[p1] += disjointSet[p2];
        disjointSet[p2] = p1;
    }
    else
    {
        disjointSet[p2] += disjointSet[p1];
        disjointSet[p1] = p2;
    }
    return true;
}

double getDistance(City& c1, City& c2)
{
    return sqrt((c1.x - c2.x) * (c1.x - c2.x) + (c1.y - c2.y) * (c1.y - c2.y));
}

void kruskcal(int n, int thr)
{
    int cnt = 0; //州的數量
    double roadDis = 0.0; // 路
    double railDis = 0.0; // 鐵路
    sort(edges.begin(), edges.end());
    int edgeNum = 0; //已選的edge數(全部有n - 1)
    for (Edge& edge: edges)
    {
        if (edgeNum == n - 1) break;
        if (!Union(edge.u, edge.v)) continue;
        if (edge.w > thr)
        {
            railDis += edge.w;
            ++cnt;
        }
        else
            roadDis += edge.w;
        ++edgeNum;
    }
    //州數+1是因為州的數量等於長度大於thr的邊數+1
    ++cnt;
    //round
    roadDis = (int)(roadDis + 0.5);
    railDis = (int)(railDis + 0.5);
    printf("%d %d %d\n", cnt, (int)roadDis, (int)railDis);
}

int main()
{
    int T;
    int n, thr;
    int x, y;
    scanf("%d", &T);
    for (int t = 1; t <= T; ++t)
    {
        scanf("%d %d", &n, &thr);
        fill(disjointSet, disjointSet + n, -1);
        // fill(cities, cities + n, City()); // 底下會複寫
        edges.clear();
        for (int i = 0; i < n; ++i)
        {
            scanf("%d %d", &x, &y);
            cities[i] = {x, y};
        }
        // 所有city兩兩相連
        for (int i = 0; i < n; ++i)
        {
            for (int j = i + 1; j < n; ++j)
            {
                edges.push_back({i, j, getDistance(cities[i], cities[j])});
            }
        }
        printf("Case #%d: ", t);
        kruskcal(n, thr);
    }
    return 0;
}