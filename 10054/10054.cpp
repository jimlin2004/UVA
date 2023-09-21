#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

struct Edge
{
    int u, v;
};

int n;
vector<vector<int>> G;
bool visited[55][55]; // visited[u][v]->u到v的這條路走過了
bool haveRes;

void dfs(int u, vector<Edge>& res)
{
    for (int v: G[u])
    {
        if (visited[u][v])
            continue;
        visited[u][v] = true;
        res.emplace_back(Edge{u, v});
        if (res.size() == n)
        {
            if (res[0].u == res[res.size() - 1].v)
            {
                for (Edge& edge: res)
                {
                    printf("%d %d\n", edge.u, edge.v);
                }
                haveRes = true;
                return;
            }
        }
        dfs(v, res);
        if (haveRes)
            return;
        res.pop_back();
        visited[u][v] = false;
    }
}

int main()
{
    int T;
    int u, v;
    scanf("%d", &T);
    for (int Case = 1; Case <= T; ++Case)
    {
        scanf("%d", &n);
        G.assign(55, vector<int>());
        for (int i = 0; i < n; ++i)
        {
            scanf("%d %d", &u, &v);
            G[u].emplace_back(v);
        }

        
    }
}