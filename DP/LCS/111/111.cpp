#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

// Note: 這題似乎只有一大組側資

//題目: 4 3 1 2->第一個事件發生在order 4，第二個事件發生在order 3...
int dp[25][25];//LCS

int main()
{
    int n;
    scanf("%d", &n);
    int correctOrder[25]; // 解答題目輸入
    int correct[25]; // 解答事件的順序
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &correctOrder[i]);
        correct[correctOrder[i]] = i;
    }

    int ansOrder[25]; // 學生題目輸入
    int ans[25]; // 學生答的事件順序
    while (scanf("%d", &ansOrder[1]) != EOF)
    {
        ans[ansOrder[1]] = 1;
        for (int i = 2; i <= n; ++i)
        {
            scanf("%d", &ansOrder[i]);
            ans[ansOrder[i]] = i;
        }

        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                if (correct[i] == ans[j])
                {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                }
                else
                {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        printf("%d\n", dp[n][n]);
    }
    return 0;
}