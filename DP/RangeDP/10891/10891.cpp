#include <bits/stdc++.h>
using namespace std;

/*

    經典deque取左右的dp
    這題拿者可以一直拿
    
    由於只能拿一個的dp概念很簡單，所以先推只能拿一次的
    定義dp[l][r]代表剩下l ~ r時拿者能夠擁有的最大差距
    轉移式: dp[l][r] = max{a[l] - dp[l + 1][r], a[r] - dp[l][r - 1]}
    其中用減的是因為要不斷地換手，所以可以看到dp就是枚舉所有的可能

    那麼可以一直拿的也很簡單
    在枚舉dp[l][r]時，需要考慮所有dp[l][r] = max{a[l ~ m] - dp[m + 1][r], a[m ~ r] - dp[l][m - 1]}，l <= m <= r
    這樣就能找到這題的答案
    上面做法需要O(n ^ 3)，這題n <= 100會過


    但其實有O(n ^ 2)的解法(這裡沒有程式)
    做法是一樣利用dp[i][j]，另外定義
    f[i][j] = min{dp[i][j], dp[i + 1][j], ..., dp[j][j]}
    g[i][j] = min{dp[i][j], dp[i][j - 1], ..., dp[i][i]}
    上面的 f 跟 g 可以用維護的
    也就是類似前綴和
    f[i][j] = min{dp[i][j], f[i + 1][j]}
    g[i][j] = min{dp[i][j], g[i][j - 1]}
    此時
    dp[i][j] = sum(i ~ j) - min{f[i + 1][j], g[i][j - 1], 0}
    最後答案在2 * dp[1][n] - sum(1 ~ n)
*/

#define maxn 105

bool vis[maxn][maxn];
long long dp[maxn][maxn];
long long a[maxn];


long long solve(int l, int r)
{
    if (l > r)
        return 0;
    if (vis[l][r])
        return dp[l][r];
    if (l == r)
        return dp[l][r] = a[l];
    
    vis[l][r] = true;

    long long res = -0x3f3f3f3f3f3f3f3f;
    long long gain = 0;
    for (int m = l; m <= r; ++m)
    {
        gain += a[m];
        res = max(res, gain - solve(m + 1, r));
    }

    gain = 0;
    for (int m = r; m >= l; --m)
    {
        gain += a[m];
        res = max(res, gain - solve(l, m - 1));
    }

    return dp[l][r] = res;
}


int main()
{
    int n;
    while (scanf("%d", &n) && n)
    {
        memset(vis, 0, sizeof(vis));
        memset(dp, 0, sizeof(dp));

        for (int i = 1; i <= n; ++i)
        {
            scanf("%lld", &a[i]);
        }

        printf("%lld\n", solve(1, n));
    }
    return 0;
}