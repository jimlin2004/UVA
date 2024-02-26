#include <cstdio>

#define maxn 30005

int coins[] = {1, 5, 10, 25, 50};
long long dp[maxn];

int main()
{
    dp[0] = 1;
    for (int i = 0; i < 5; ++i)
    {
        for (int j = coins[i]; j < maxn; ++j)
        {
            dp[j] += dp[j - coins[i]];
        }
    }

    int n;
    while (scanf("%d", &n) != EOF)
    {
        if (dp[n] == 1)
            printf("There is only 1 way to produce %d cents change.\n", n);
        else
            printf("There are %lld ways to produce %d cents change.\n", dp[n], n);
    }

    return 0;
}