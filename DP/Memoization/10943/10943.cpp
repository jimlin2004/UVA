#include <cstdio>
#include <cstring>
using namespace std;

#define MAXN 105

int n, k;
int dp[MAXN][MAXN]; //dp[i][j] -> i拆成j個數字的方法數
const int mod = 1e6;

// ex: 12 拆成3份
// currN  -> 目前剩下的N
// remain -> 現在剩下的K
int dfs(int remainN, int remainK)
{
    if (remainK == 1) return 1;
    if (dp[remainN][remainK] != -1) return dp[remainN][remainK];
    int result = 0;
    for (int i = 0; i <= remainN; ++i)
    {
        result += dfs(remainN - i, remainK - 1);
        result %= mod;
    }
    return dp[remainN][remainK] = result;
}

int main()
{
    memset(dp, -1, sizeof(dp));
    while (scanf("%d %d", &n, &k) != EOF && (n + k != 0))
    {
        printf("%d\n", dfs(n, k) % mod);
    }
    return 0;
}