#include <cstdio>
#include <cstring>
using namespace std;

#define maxc 305
#define MOD 1000000000

/*
    區間dp題

    只有在AxxxxxA頭尾相同時A才有可能是新的分支開頭
    當在區間枚舉所有可能的中間點時，
    中間點一定要符合str[i] == str[m] == str[j]
    剩下的就是要遞迴下去檢查
    可以找到轉移式:
        dp[i][j] = sum所有的(dp[i + 1][m - 1] * dp[m][j])
    也就是i ~ 中間點有多少可能 * 中間點到j有多少可能
    全部加起來就是i ~ j有多少可能
    細節看下方
*/

char str[maxc];
long long dp[maxc][maxc];

// 記憶化搜尋
long long solve(int i, int j)
{
    if (i > j)
        return 0;
    // 這裡是重點，當i == j時要當作一種
    if (i == j)
        return 1;
    // 當有3個字且頭尾是一樣的，那麼就一定是一種可能
    if (j - i == 2 && str[i] == str[j])
        return 1;
    if (dp[i][j] != -1)
        return dp[i][j];
    long long res = 0;
    for (int m = i + 1; m <= j; ++m)
    {
        if (str[i] == str[m] && str[m] == str[j])
        {
            res += (solve(i + 1, m - 1) * solve(m, j));
            res %= MOD;
        }
    }
    return dp[i][j] = res;
}

int main()
{
    while (scanf("%s", str) != EOF)
    {
        memset(dp, -1, sizeof(dp));
        int len = strlen(str);
        printf("%lld\n", solve(0, len - 1));
    }
    return 0;
}