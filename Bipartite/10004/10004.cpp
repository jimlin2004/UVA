#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

int color[205]; // 0 代表還沒訪未過，1、-1是不同顏色
vector<vector<int>> G;

inline int getNextColor(int c)
{
    return (c == 1) ? -1 : 1;
}

bool dfs(int u, int currColor)
{
    if (color[u] == 0)
    {
        color[u] = currColor;
    }
    bool res;
    for (int v: G[u])
    {
        if (color[v] == 0)
        {
            res = dfs(v, getNextColor(currColor));
            if (!res)
                return false;
        }
        if (color[u] == color[v])
            return false;
    }
    return true;
}

int main()
{
    int n, l;
    while (scanf("%d", &n) != EOF && n)
    {
        scanf("%d", &l);
        memset(color, 0, sizeof(color));
        G.assign(n, vector<int>());
        int u, v;
        for (int i = 0; i < l; ++i)
        {
            scanf("%d %d", &u, &v);
            G[u].emplace_back(v);
            G[v].emplace_back(u);
        }
        puts((dfs(0, 1)) ? "BICOLORABLE." : "NOT BICOLORABLE.");
    }
    return 0;
}