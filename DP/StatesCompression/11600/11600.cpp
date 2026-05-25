#include <bits/stdc++.h>
using namespace std;

/*
期望dp + 狀壓
題意:
    一張完全圖，給定多個連通塊，一開始站在node 1的連通塊，之後每次隨機抽一個不是自己在的node，就能連結自己的連通塊以及新的連通塊
    問期望多少次可以讓所有連通塊合併?
解法:
    因為只有30個node，且有一些edge已經可以走了
    所以先將連通塊縮點
    用狀壓int的30個bit代表該連通塊完成能不能走到了
    dp[u][state]代表站在 連通塊 u 且目前狀態為state時 到 能夠全部走到的期望天數

    首先討論目前狀態選到下一個沒有選到的連通塊機率如何計算?
    1. 假設已完成的node數為have，還沒完成的node數自然為 n - have
    2. 選到一個未完成的機率為(沒完成的) / (除了自己站在的node之外所有node數)
        -> (n - have) / (n - 1)
    3. 那麼以期望值來說，需要 (n - 1) / (n - have) [就是倒數]天才會選到一個未完成的node

    dp轉移式:
    dp[u][state] = (n - 1) / (n - have) + sum_{i 是還沒完成的連通塊} dp[i][state | (1 << i)] x ( (連通塊i的大小) / (n - have) )
    其中的意義就是 平均多少天會抽到新的node + for each i 是還沒完成的連通塊 { (如果踩到的是i號連通塊要花的dp[i][state | (1 << i)])天才能完成 x 抽到i連通塊上的node的機率 }

    詳細看下方程式

    但這個做法是O(2^n x n)
    事實上如果極限測資 30 0 會跑不完
    但這題很神奇的網路解法都是這樣解，也剛好測資會過
*/

vector<vector<int>> G;
int n, m;
// 有多少個連通塊
int gCnt;
// dfs用
bool vis[35];
// 每個連通塊的大小
int gSize[35];
// 期望 + 狀壓dp，避免空間放不下，用map離散化空間
map<int, double> dp[35];

// 用來數每個連通塊有多少個點
int dfs(int u)
{
    vis[u] = true;
    int cnt = 1;
    for (int v: G[u])
    {
        if (!vis[v])
        {
            vis[v] = true;
            cnt += dfs(v);
        }
    }

    return cnt;
}

double DP(int u, int state)
{
    if (dp[u].count(state))
        return dp[u][state];

    // 計算目前state有多少node已經走過了
    int have = 0;
    for (int i = 0; i < gCnt; ++i)
    {
        if (state & (1 << i))
        {
            have += gSize[i];
        }
    }

    // 如果都走過了，那就結束了，不需要花天數
    if (have == n)
        return 0;

    // 開始dp轉移式
    dp[u][state] = (n - 1) / (double)(n - have);

    for (int i = 0; i < gCnt; ++i)
    {
        if (state & (1 << i))
            continue;
        dp[u][state] += DP(i, state | (1 << i)) * gSize[i] / (n - have);
    }

    return dp[u][state];
}

int main()
{
    int T;
    scanf("%d", &T);

    int testcase = 0;

    while (T--)
    {
        memset(vis, 0, sizeof(vis));

        scanf("%d %d", &n, &m);

        G.assign(n + 5, {});

        for (int i = 0; i < m; ++i)
        {
            int u, v;
            scanf("%d %d", &u, &v);
            G[u].emplace_back(v);
            G[v].emplace_back(u);
        }

        // 將所有連通塊縮點
        gCnt = 0;
        for (int i = 1; i <= n; ++i)
        {
            if (!vis[i])
            {
                gSize[gCnt++] = dfs(i);
            }
        }

        for (int i = 0; i < gCnt; ++i)
        {
            dp[i].clear();
        }

        printf("Case %d: %.6lf\n", ++testcase, DP(0, 1));
    }

    return 0;
}