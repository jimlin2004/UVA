#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

/*
    題目要s到t之間的所有路徑中load可以支撐的最高上限
    Kruskal找最大生成樹保證兩點之間路徑唯一
    再用dfs找出s到t的那條唯一的路徑上的最小load即可
*/

#define maxn 205

struct Edge
{
    int u, v, w;
    bool operator < (const Edge& other) const
    {
        return this->w > other.w;
    }
};

//用於地名與編號的轉換
unordered_map<string, int> mp;
int lastIndex = 0;

vector<Edge> edges;
vector<vector<Edge>> G;

int parent[maxn];

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

void kruskal(int n)
{
    int count = 0;
    
    sort(edges.begin(), edges.end());
    for (const Edge& edge: edges)
    {
        if (Union(edge.u, edge.v))
        {
            ++count;
            G[edge.u].emplace_back(Edge{edge.u, edge.v, edge.w});
            G[edge.v].emplace_back(Edge{edge.v, edge.u, edge.w});
            if (count == n - 1)
                break;
        }
    }
}

//搜尋直到找到t，並回傳一路上的最小load，否則回傳0x3f3f3f3f
int dfs(int u, int p, int t, int load)
{
    int res = 0x3f3f3f3f;
    if (u == t)
    {
        return load;
    }
    for (const Edge& edge: G[u])
    {
        if (edge.v != p)
        {
            res = min(res, dfs(edge.v, edge.u, t, min(load, edge.w)));
        }
    }
    return res;
}

int main()
{
    int Case = 0;
    int n, r;
    while (cin >> n >> r)
    {
        if (n == 0 && r == 0)
            break;
        string su, sv;
        int u, v, w;
        mp.clear();
        lastIndex = 0;
        edges.clear();
        G.assign(n + 5, vector<Edge>());
        memset(parent, -1, sizeof(parent));
        
        for (int i = 0; i < r; ++i)
        {
            cin >> su >> sv >> w;
            if (mp.find(su) == mp.end())
            {
                mp[su] = lastIndex;
                u = lastIndex;
                ++lastIndex;
            }
            else
                u = mp[su];
            if (mp.find(sv) == mp.end())
            {
                mp[sv] = lastIndex;
                v = lastIndex;
                ++lastIndex;
            }
            else
                v = mp[sv];

            edges.emplace_back(Edge{u, v, w});
            edges.emplace_back(Edge{v, u, w});
        }

        kruskal(n);

        cin >> su >> sv;
        u = mp[su];
        v = mp[sv];

        printf("Scenario #%d\n", ++Case);

        printf("%d tons\n\n", dfs(u, -1, v, 0x3f3f3f3f));
    }
    return 0;
}