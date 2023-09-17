#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

vector<vector<int>> G;
bool visited[10005];
int res;

void dfs(int u)
{
    if (visited[u])
        return;
    visited[u] = true;
    ++res;
    for (int v: G[u])
    {
        dfs(v);
    }
}

int main()
{
    int Case;
    scanf("%d", &Case);
    int n, m, l;
    while (Case--)
    {
        scanf("%d %d %d", &n, &m, &l);
        G.assign(n + 1, vector<int>());
        memset(visited, false, sizeof(visited));
        res = 0;
        int u, v;
        for (int i = 0; i < m; ++i)
        {
            scanf("%d %d", &u, &v);
            G[u].emplace_back(v);
        }
        int s;
        for (int i = 0; i < l; ++i)
        {
            scanf("%d", &s);
            dfs(s);
        }

        printf("%d\n", res);
    }
    return 0;
}