#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

//類似無限背包，改用min

int squares[105];
int dp[10005];

int main()
{
    for (int i = 1; i < 105; ++i)
    {
        squares[i] = i * i;
    }

    memset(dp, 0x3f, sizeof(dp));

    dp[0] = 0;
    dp[1] = 1;

    for (int i = 1; i <= 100; ++i)
    {
        for (int j = squares[i]; j <= 10000; j++)
        {
            dp[j] = min(dp[j - squares[i]] + 1, dp[j]);
        }
    }

    int t, n;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &n);
        printf("%d\n", dp[n]);
    }
    return 0;
}