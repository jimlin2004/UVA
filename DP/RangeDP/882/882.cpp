#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

/*
    題意，給k個郵筒，現在最多有m個鞭炮，求最少炸多少個鞭炮可以確定郵筒最多能承受多少鞭炮

    dp題，重點是定義dp
    定義dp[k][i][j]指的是現在有k個郵筒，目前需要確認最少可能炸毀郵筒的鞭炮數量為i，最多為j
    那dp就很簡單了，區間dp的想法，
    i~j之間一定存在一個 m 可以炸毀郵筒且可以最少步數
    所以枚舉中間點 m (i <= m <= j)
    dp[k][i][j]一開始設為無限大
    轉移式dp[k][i][j] = min(dp[k][i][j], m + max(dp[k - 1][i][m - 1], dp[k][m + 1][j]))
    其中dp[k - 1][i][m - 1]是郵筒被炸毀了，所以郵筒的承受力確定在i ~ m - 1之間
    dp[k][m + 1][j]是郵筒沒有被炸毀，所以郵筒的承受力確定在m + 1 ~ j之間
*/

#define maxm 105

bool vis[15][maxm][maxm];
long long dp[15][maxm][maxm];

long long solve(int k, int i, int j)
{
    //這個邊界狀況回傳0
    if (i > j)
        return 0;
    if (vis[k][i][j])
        return dp[k][i][j];
    vis[k][i][j] = true;
    //當k等於0就沒得炸，那就回傳無限大
    if (k == 0)
        return 0x3f3f3f3f3f3f3f3f;
    long long res = 0x3f3f3f3f3f3f3f3f;
    for (int m = i; m <= j; ++m)
    {
        res = min(res, m + max(solve(k - 1, i, m - 1), solve(k, m + 1, j)));
    }
    
    return dp[k][i][j] = res;
}

int main()
{
    int T;
    scanf("%d", &T);
    //注意這題的陣列不用刷新，因為答案算過之後不會變
    memset(vis, 0, sizeof(vis));
    memset(dp, 0x3f, sizeof(dp));
    while (T--)
    {
        int k, m;
        scanf("%d %d", &k, &m);
        printf("%lld\n", solve(k, 1, m));
    }
    return 0;
}