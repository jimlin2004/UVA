#include <cstdio>
using namespace std;

/*
    照著規則寫就行
    dp[i][0] 代表在level i不分支的
    dp[i][1] 代表在level i會分支的
    DP轉移:
    dp[i][0] = dp[i - 1][1];
    dp[i][1] = dp[i - 1][0] + dp[i - 1][1];
*/

#define maxn 90

unsigned long long dp[maxn][2];

int main()
{
    dp[0][0] = 1;
    dp[0][1] = 0;
    dp[1][0] = 1;
    dp[1][1] = 0;
    for (int i = 2; i < maxn; ++i)
    {
        dp[i][0] = dp[i - 1][1];
        dp[i][1] = dp[i - 1][0] + dp[i - 1][1];
    }

    int n;
    while (scanf("%d", &n) && n)
    {
        printf("%llu\n", dp[n][0] + dp[n][1]);
    }
    return 0;
}