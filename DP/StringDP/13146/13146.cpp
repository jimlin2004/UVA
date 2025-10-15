#include <bits/stdc++.h>
using namespace std;

/*
    dp[i][j] -> s1的前i個與s2的前j個變成一樣的編輯距離
*/
int dp[105][105];
char s1[105];
char s2[105];

int main()
{
    int T;
    cin >> T;
    cin.ignore();

    while (T--)
    {
        string s1, s2;
        getline(cin, s1);
        getline(cin, s2);

        int n = s1.size();
        int m = s2.size();

        memset(dp, 0, sizeof(dp));

        // 全部刪掉
        for (int i = 1; i <= n; ++i)
            dp[i][0] = i;
        
        // 全部加入字元
        for (int j = 1; j <= m; ++j)
            dp[0][j] = j;

        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                // 如果這個字兩邊一樣，就不用成本
                if (s1[i - 1] == s2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1];
                else 
                    dp[i][j] = min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]}) + 1;
                /* 
                    加一個字 (也就是s1[i - 1]後面加上一個s2[j - 1]) -> dp[i - 1][j] + 1,
                    刪字 (也就是刪除s1[i - 1])                     -> dp[i][j - 1] + 1, 
                    替換 (也就是s1[i - 1]換成s2[j - 1])            -> dp[i - 1][j - 1] + 1
                */
            }
        }

        printf("%d\n", dp[n][m]);
    }

    return 0;
}