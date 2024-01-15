#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

//要把錢分的最平均，相當於要找出全部錢一半的最大值分法(0、1背包問題)

//dp[i][j] 只買前i個東西時剩下j個空間的總價值
//dp[i][j] = max(dp[i - 1][j], dp[i][j - coins[i]])
//空間壓縮
//50000 -> 100 * 500
int dp[50005];
int price[105];

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int n;
        int totP = 0;
        memset(dp, 0, sizeof(dp));
        scanf("%d", &n);
        for (int i = 0; i < n; ++i)
        {
            scanf("%d", &price[i]);
            totP += price[i];
        }

        for (int i = 0; i < n; ++i)
        {
            for (int remain = (totP / 2); remain >= price[i]; --remain)
                dp[remain] = max(dp[remain], dp[remain - price[i]] + price[i]);
        }
        printf("%d\n", abs(totP - dp[(totP / 2)] * 2));
    }
    return 0;
}