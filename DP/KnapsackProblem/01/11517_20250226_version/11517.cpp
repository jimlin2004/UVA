#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

/*
    背包變種題
    重點在錢的面額與商品價值不會超過10000
    所以可以用背包的方式
    最糟糕的情況下會花9999 + 9999的錢去買一個商品
    所以直接變成當現在是dp[i] = cnt -> 用cnt種coins可以湊成i元
    用背包的方式 dp[i] = min(dp[i], dp[i - coins[j]] + 1)可以找到
    用最少cnt種coins可以湊成i元
    之後再直接從price往上搜第一個可以湊出的錢即為答案
*/

#define maxn 20005

int coins[105];

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int price;
        scanf("%d", &price);
        int n;
        scanf("%d", &n);

        int c;
        for (int i = 0; i < n; ++i)
        {
            scanf("%d", &coins[i]);
        }

        int dp[maxn];
        memset(dp, 0x3f, sizeof(dp));

        dp[0] = 0;
        for (int j = 0; j < n; ++j)
        {
            for (int i = maxn - 1; i >= coins[j]; --i)
            {
                dp[i] = min(dp[i], dp[i - coins[j]] + 1);
            }
        }

        int res = 0;
        int resCnt = 0;
        // 找第一個可以湊出來的數值
        for (int i = price; i < maxn; ++i)
        {
            if (dp[i] != 0x3f3f3f3f)
            {
                res = i;
                resCnt = dp[i];
                break;
            }
        }
        printf("%d %d\n", res, resCnt);
    }
    return 0;
}
