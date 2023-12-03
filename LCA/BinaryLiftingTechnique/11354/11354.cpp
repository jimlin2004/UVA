#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

#define maxn 50005

/*
MST + dfs
每次dfs查詢O(n)在這題過不了
*/

struct Edge
{
    int u, v, w;
    bool operator < (const Edge& other) const
    {
        return this->w < other.w;
    }
};

int parent[maxn];
vector<Edge> edges;
vector<vector<Edge>> G; //MST

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

void kurskal(int n)
{
    memset(parent, -1, sizeof(parent));
    sort(edges.begin(), edges.end());

    int count = 0;
    for (const Edge& edge: edges)
    {
        if (Union(edge.u, edge.v))
        {
            G[edge.u].emplace_back(Edge{edge.u, edge.v, edge.w});
            G[edge.v].emplace_back(Edge{edge.v, edge.u, edge.w});
            ++count;
        }

        if (count == n - 1)
            break;
    }
}

//在MST的DFS
//取出到target的path中weight最大的
//只有到target的path才會回傳path中的最大weight
//其餘回傳-1
int dfs(int u, int p, int target, int currW)
{
    if (u == target)
    {
        return currW;
    }
    int res = -1;
    for (const Edge& edge: G[u])
    {
        if (edge.v == p)
            continue;
        res = max(res, dfs(edge.v, edge.u, target, max(currW, edge.w)));
    }
    return res;
}

int main()
{
    //test case 之間有空白行，用cin較輕鬆
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    bool first = true;
    while (cin >> n >> m)
    {
        G.assign(n + 5, vector<Edge>());
        edges.clear();
        int u, v, w;
        for (int i = 0; i < m; ++i)
        {
            cin >> u >> v >> w;
            //雙向，但對kurskal沒差
            edges.emplace_back(Edge{u, v, w});
        }

        kurskal(n);
        int q;
        cin >> q;
        int source, target;
        if (first)
            first = false;
        else
            cout << '\n';
        while (q--)
        {
            cin >> source >> target;
            cout << dfs(source, -1, target, -1) << '\n';
        }
    }
    return 0;
}