#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

/*
核心:
    題目提到任兩點只有一條路徑->題目是一顆tree
    最小點覆蓋問題->樹形dp
    dp[u][0 or 1]->節點u裝不裝安全門
    轉移式
    u不裝->子節點一定要裝
    u裝  ->子節點可裝可不裝
    dp[u][0] = sum(v is child of u dp[v][1])
    dp[u][1] = sum(v is child of u min(dp[v][0], dp[v][1])) + 1
    特判:
        只有一節點時輸出1
*/

vector<vector<int>> G;
bool visited[1005];
int dp[1005][2]; // dp[u][0 or 1]代表節點i裝或不裝安全門

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

void solve()
{
    dfs(1);
    printf("%d\n", min(dp[1][0], dp[1][1]));
}

int main()
{
    int N;
    while (~scanf("%d", &N) && N)
    {
        G.assign(N + 5, vector<int>());
        memset(visited, 0, sizeof(visited));
        memset(dp, 0, sizeof(dp));
        int t, v;
        for (int u = 1; u <= N; ++u)
        {
            scanf("%d", &t);
            while (t--)
            {
                scanf("%d", &v);
                G[u].emplace_back(v);
            }
        }

        if (N == 1)
            puts("1");
        else
        {
            solve();
        }
    }
    return 0;
}