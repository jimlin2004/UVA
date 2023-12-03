#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

#define maxn 50005

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

int fa[maxn][31]; //fa[u][i] -> u的第2^1的祖先
int maxW[maxn][31];
int depth[maxn];

void dfs(int u, int p)
{
    fa[u][0] = p;
    depth[u] = depth[p] + 1;
    for (int i = 1; i < 31; ++i)
    {
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
        maxW[u][i] = max(maxW[fa[u][i - 1]][i - 1], maxW[u][i - 1]);
    }

    for (const Edge& edge: G[u])
    {
        if (edge.v == p)
            continue;
        maxW[edge.v][0] = edge.w;
        dfs(edge.v, u);
    }
}

int query(int x, int y)
{
    //讓y比x深
    if (depth[x] > depth[y])
        swap(x, y);
    int deltaDep = depth[y] - depth[x];
    int res = 0;

    //讓y與x在同一深度
    for (int i = 0; deltaDep != 0; ++i, deltaDep >>= 1)
    {
        if (deltaDep & 1)
        {
            res = max(res, maxW[y][i]);
            y = fa[y][i];
        }
    }

    if (y == x)
        return res;

    for (int i = 30; i >= 0 && y != x; --i)
    {
        if (fa[x][i] != fa[y][i])
        {
            res = max({res, maxW[x][i], maxW[y][i]});
            x = fa[x][i];
            y = fa[y][i];
        }
    }

    res = max({res, maxW[x][0], maxW[y][0]});
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
        
        for (int i = 0; i < q; ++i)
        {
            cin >> source >> target;
            //建sparse_table
            if (i == 0)
                dfs(source, 0);
            cout << query(source, target) << '\n';
        }
    }
    return 0;
}