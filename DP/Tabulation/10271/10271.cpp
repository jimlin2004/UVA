#include <bits/stdc++.h>
using namespace std;

/*

題意: 一組筷子的cost是(最短的兩根差值)^2，最長的一根可以當作不存在
為了保證永遠有一根最長的筷子可以用，所以題目給的遞增數列倒過來存變成由大到小
這樣一來可以保證組合一定有一根最長的
定義dp: dp[i][j] -> 組成i組時用了前j根筷子
轉移式:
    if (j >= i * 3) // 大於等於 3i 根筷子才能湊出i組以上
        dp[i][j] = min(dp[i][j - 1], dp[i - 1][j - 2] + (chopsticks[j] - chopsticks[j - 1]) * (chopsticks[j] - chopsticks[j - 1]));
    當我決定要用現在這根新的第j根筷子時，長度距離它最近的一定是第j - 1根筷子(因為數列由大到小)
    所以要用j時j - 1也要一起用
    如此我只要討論要不要使用j與j - 1並保留最好的組合
    所以
    dp[i][j]與dp[i][j - 1] -> 不用第j根還有
    dp[i - 1][j - 2] + (chopsticks[j] - chopsticks[j - 1]) * (chopsticks[j] - chopsticks[j - 1]) -> 使用第j根與第j - 1根
    有關
*/

int chopsticks[5005];
int dp[1005][5005]; // dp[i][j] -> 組成i組時用了前j根筷子

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int k, n;
        scanf("%d %d", &k, &n);

        k += 8;

        memset(dp, 0x3f, sizeof(dp));

        // 由大到小放
        for (int i = n; i > 0; --i)
            scanf("%d", &chopsticks[i]);
        
        for (int i = 0; i <= n; ++i)
            dp[0][i] = 0;
        
        for (int i = 1; i <= k; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                if (j >= i * 3) // 大於等於 3i 根筷子才能湊出i組以上
                    dp[i][j] = min(dp[i][j - 1], dp[i - 1][j - 2] + (chopsticks[j] - chopsticks[j - 1]) * (chopsticks[j] - chopsticks[j - 1]));
            }
        }

        printf("%d\n", dp[k][n]);
    }

    return 0;
}