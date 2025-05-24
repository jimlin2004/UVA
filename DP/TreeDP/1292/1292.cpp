#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

/*
核心:
    最小點覆蓋問題->樹形dp
    dp[u][0 or 1]->節點u放不放
    轉移式
    u不放->子節點一定要放
    u放  ->子節點可放可不放
    dp[u][0] = sum(v is child of u dp[v][1])
    dp[u][1] = sum(v is child of u min(dp[v][0], dp[v][1])) + 1
    特判:
        只有一節點時輸出1
    <Note> 此題不保證只有一顆tree，可能是森林，所以要用visited去檢查並遍歷所有節點
*/

#define MAXN 1505

int dp[MAXN][2];
bool visited[MAXN];
vector<vector<int>> G;

void dfs(int u)
{
    visited[u] = true;

    for (int v: G[u])
    {
        if (visited[v])
            continue;
        dfs(v);
        dp[u][0] += dp[v][1];
        dp[u][1] += min(dp[v][0], dp[v][1]);
    }
    ++dp[u][1];
}

void solve(int n)
{
    int res = 0;
    for (int u = 0; u < n; ++u)
    {
        if (!visited[u])
        {
            dfs(u);
            res += min(dp[u][0], dp[u][1]);
        }
    }
    printf("%d\n", res);
}

int main()
{
    int n;
    while (~scanf("%d", &n) && n)
    {
        memset(dp, 0, sizeof(dp));
        memset(visited, 0, sizeof(visited));
        G.assign(n + 5, vector<int>());

        int u, v, t;
        for (int i = 0; i < n; ++i)
        {
            scanf("%d:(%d)", &u, &t);
            while (t--)
            {
                scanf("%d", &v);
                G[u].emplace_back(v);
                G[v].emplace_back(u);
            }
        }

        if (n == 1)
            puts("1");
        else
        {
            solve(n);
        }
    }
    return 0;
}