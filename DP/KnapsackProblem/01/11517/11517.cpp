#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int coins[105];
int dp[20005];

//01背包，每種面額只能用一次

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int target;
        scanf("%d", &target);
        memset(dp, 0x3f, sizeof(dp));
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; ++i)
            scanf("%d", &coins[i]);
        dp[0] = 0;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 20004; j >= coins[i]; j--)
            {
                dp[j] = min(dp[j - coins[i]] + 1, dp[j]);
            }
        }
        for (int i = target; i < 20005; ++i)
        {
            if (dp[i] != 0x3f3f3f3f)
            {
                printf("%d %d\n", i, dp[i]);
                break;
            }
        }
    }
    return 0;
}