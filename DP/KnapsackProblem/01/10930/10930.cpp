#include <bits/stdc++.h>
using namespace std;

/*
    用0 1背包維護哪些數字能夠使用前面的數字湊出即可
    另外不用擔心dp[]裡有一些數字是只用一個數字湊出的
    因為在dp檢查之前會先檢查單調上升
    若檢查A[i]時在dp[A[i]]裡是true
    代表A[i]是由兩個以上的數字湊出，而不會是僅一個數字
*/

#define maxs 30005

int A[35];
bool dp[maxs];

int main()
{
    int tc = 0;
    int n;
    while (scanf("%d", &n) != EOF)
    {
        memset(dp, 0, sizeof(dp));

        dp[0] = true;
        bool res = true;

        for (int i = 1; i <= n; ++i)
        {
            scanf("%d", &A[i]);
        }

        for (int i = 1; i <= n; ++i)
        {
            if (i == 1 && A[i] < 1)
            {
                res = false;
                break;
            }
            else if (A[i - 1] >= A[i])
            {
                res = false;
                break;
            }
        }
            
        if (res)
        {
            for (int i = 1; i <= n; ++i)
            {
                // 先檢查
                if (dp[A[i]])
                {
                    res = false;
                    break;
                }

                if (!res)
                    break;

                // 再維護dp
                for (int j = maxs - 1; j >= A[i]; j--)
                    dp[j] |= dp[j - A[i]];
            }
        }


        printf("Case #%d:", ++tc);
        for (int i = 1; i <= n; ++i)
            printf(" %d", A[i]);
        puts("");
        puts((res) ? "This is an A-sequence." : "This is not an A-sequence.");
    }

    return 0;
}