#include <cstdio>
using namespace std;

int coins[] = {
    5, 10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000
};

long long dp[30005];

int main()
{
    int part1, part2;
    
    // 核心概念: 
    // dp[i][j]: i -> 只使用前i個面額，湊出金額j的湊法
    // 邊界條件dp[0][..] = 0, dp[..][0] = 1
    // 可以發現dp[i][j] = dp[i - 1][j] + dp[i][j - coins[i]]
    // dp[j] += dp[j - coins[i]]是空間壓縮
    // (dp[i][..]只與dp[i][..]和dp[i - 1][..]有關) -> 滾動陣列
    dp[0] = 1;

    for (int i = 0; i < 11; ++i)
    {
        for (int j = coins[i]; j < 30001; ++j)
        {
            dp[j] += dp[j - coins[i]];
        }
    }

    while (scanf("%d.%d", &part1, &part2) != EOF)
    {
        if (part1 == 0 && part2 == 0)
            break;
        printf("%3d.%02d%17lld\n", part1, part2, dp[part1 * 100 + part2]);
    }
    return 0;
}