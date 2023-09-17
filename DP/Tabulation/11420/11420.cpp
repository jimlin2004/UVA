#include <cstdio>
using namespace std;

// dp[n][s][t] n: 幾個抽屜 s: 幾個是安全的 t: (0 or 1) 最上面的抽屜是U or L
// 分兩種case
// case 1: dp[n][s][0] = dp[n - 1][s + 1][1] + dp[n - 1][s][0]
// 此時最上面放U，則
// dp[n - 1][s + 1][1]: 現在要放的U會導致底下n - 1個抽屜最上面L變不安全，為了得到n個抽屜s個安全，所以要s + 1
// dp[n - 1][s][0]: n - 1個抽屜有s個安全，現在在其上面再放一個U不影響S的數量
// case 2: dp[n][s][1] = dp[n - 1][s - 1][1] + dp[n - 1][s - 1][0]
// 在最上面放L，底下n - 1個抽屜有s - 1個安全，無論上方是U、L皆不影響

long long dp[70][70][2];

int main()
{
    int n, s;
    
    // 初始條件
    dp[1][0][0] = dp[1][1][1] = 1;

    for (int i = 2; i <= 66; ++i)
    {
        // i個抽屜0個安全且上方0 = (底下i - 1個抽屜且1個安全且最上面L) + (底下n - 1個抽屜0個安全且最上方為0)
        dp[i][0][0] = dp[i - 1][1][1] + dp[i - 1][0][0];

        for (int j = 1; j <= i; ++j)
        {
            dp[i][j][0] = dp[i - 1][j + 1][1] + dp[i - 1][j][0];
            dp[i][j][1] = dp[i - 1][j - 1][1] + dp[i - 1][j - 1][0];
        }
    }
    while (scanf("%d %d", &n, &s) != EOF)
    {
        if (n < 0 && s < 0)
            break;
        printf("%lld\n", dp[n][s][0] + dp[n][s][1]);
    }
    return 0;
}