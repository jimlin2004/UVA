#include <cstdio>

int coins[] = {1, 5, 10, 25, 50};
int dp[8000];
//dp[i][j] -> 只用前i種面額湊出總共j的方法數
//dp[i][j] = dp[i - 1][j] + dp[i][j - coints[i]]
//空間壓縮: dp[j] += dp[j - coints[i]]

int main()
{
    dp[0] = 1;
    for (int i = 0; i < 5; ++i)
    {
        for (int j = coins[i]; j < 8000; ++j)
        {
            dp[j] += dp[j - coins[i]];
        }
    }
    int p;
    while (scanf("%d", &p) != EOF)
    {
        printf("%d\n", dp[p]);
    }
    return 0;
}