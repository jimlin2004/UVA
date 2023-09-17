#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

struct City
{
    int x, y;
    int p;
    double operator - (const City& other) const
    {
        return sqrt((this->x - other.x) * (this->x - other.x) +
            (this->y - other.y) * (this->y - other.y));
    }
};

struct Edge
{
    int u, v;
    double w;
    bool operator < (const Edge& other) const
    {
        return this->w < other.w;
    }
};

vector<Edge> edges;
vector<vector<Edge>> G;
vector<City> cities;
int parent[1005];
int n; // 點的個數
double totalCost;

//maxCost[x][y]是x到y的路徑中cost最大的那一個edge的cost
double maxCost[1005][1005];
bool visited[1005];

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

void kurskal()
{
    //利用最小生成樹建圖
    int edgeNum = 0;
    totalCost = 0;
    sort(edges.begin(), edges.end());
    for (const Edge& edge: edges)
    {
        if (Union(edge.u, edge.v))
        {
            ++edgeNum;
            totalCost += edge.w;

            //建圖(無向)
            G[edge.u].emplace_back(Edge{edge.u, edge.v, edge.w});
            G[edge.v].emplace_back(Edge{edge.v, edge.u, edge.w});

            if (edgeNum == n - 1)
                break;
        }
    }
}

// Time limit
// void floydWarshall() O(V^3)
// {
//     fill_n(&maxCost[0][0], sizeof(maxCost) / sizeof(maxCost[0][0]), 0x3f3f3f3f);

//     for (vector<Edge>& vec: G)
//     {
//         for (Edge& edge: vec)
//         {
//             maxCost[edge.u][edge.v] = edge.w;
//         }
//     }

//     for (int k = 0; k < n; ++k)
//         for (int x = 0; x < n; ++x)
//             for (int y = 0; y < n; ++y)
//                 maxCost[x][y] = min(maxCost[x][y], max(maxCost[x][k], maxCost[k][y]));
// }

void dfs(int u)//用於得到maxCost O(V^2)
{
    visited[u] = true;
    for (Edge& edge: G[u])
    {
        if (visited[edge.v])
            continue;
        for (int i = 0; i < n; ++i)
        {
            if (visited[i])
                maxCost[edge.v][i] = maxCost[i][edge.v] = max(maxCost[u][i], edge.w);
        }
        dfs(edge.v);
    }
}

int main()
{
    int Case;
    scanf("%d", &Case);
    while (Case--)
    {
        scanf("%d", &n);
        int x, y, p;

        cities.clear();
        edges.clear();
        G.assign(n, vector<Edge>());
        memset(parent, -1, sizeof(parent));
        memset(visited, false, sizeof(visited));
        memset(maxCost, 0, sizeof(maxCost));
        for (int i = 0; i < n; ++i)
        {
            scanf("%d %d %d", &x, &y, &p);
            cities.emplace_back(City{x, y, p});
        }

        for (int i = 0; i < n; ++i)
        {
            for (int j = i + 1; j < n; ++j)
            {
                edges.push_back(Edge{i, j, cities[i] - cities[j]});
            }
        }

        kurskal();
        dfs(0);
        // floydWarshall();

        double res = 0;
        int subtotalP; // city i 與 city j 的居民數
        double subtotalCost; // 去掉魔法路的cost
        for (int i = 0; i < n; ++i)
        {
            for (int j = i + 1; j < n; ++j)
            {
                subtotalP = cities[i].p + cities[j].p;
                subtotalCost = totalCost - maxCost[i][j];
                res = max(res, subtotalP / subtotalCost);
            }
        }
        printf("%.2lf\n", res);
    }
    return 0;
}