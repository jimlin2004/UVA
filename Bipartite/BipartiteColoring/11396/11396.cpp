#include <bits/stdc++.h>
using namespace std;

/*
    因為每個點一定是3個邊 (題目限制)
    所以如果u是雞爪的中心點，那他的三個小孩就只能當作其他雞爪的腳
    (因為小孩v的一個邊已經被u選走了，那v就沒有三個沒選過的邊可以當雞爪中心)

    所以整張圖的任意路徑就是中心、腳、中心、腳、...
    因此這問題就是塗色問題，dfs一次就行了
    (注意圖沒有保證全連接)
*/

vector<vector<int>> G;

int color[305];

bool dfs(int u, int c)
{
    color[u] = c;
    for (int v: G[u])
    {
        if (color[v] == -1)
        {
            if (!dfs(v, 1 - c))
                return false;
        }
        if (color[v] == color[u])
            return false;
    }
    return true;
}

int main()
{
    int n;
    while (scanf("%d", &n) && n)
    {
        G.assign(n + 5, {});

        int u, v;
        while (scanf("%d %d", &u, &v))
        {
            if (u == 0 && v == 0)
                break;
            G[u].push_back(v);
            G[v].push_back(u);
        }

        memset(color, -1, sizeof(color));

        bool ok = true;
        for (int u = 1; u <= n; ++u)
        {
            // 不一定全連通，所以每個點都要檢查
            if (color[u] == -1)
            {
                if (!dfs(u, 0))
                {
                    ok = false;
                    break;
                }
            }
        }

        puts((ok) ? "YES" : "NO");
    }

    return 0;
}

/*
8
1 6
1 7
1 8
2 6
2 8
2 5
4 8
4 7
4 5
3 5
3 6
3 7
0 0
*/