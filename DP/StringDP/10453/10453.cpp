#include <bits/stdc++.h>
using namespace std;

/*
    dp下去找最少操作步數
    記下最好操作
    遞迴print
*/

#define maxn 1005

int dp[maxn][maxn];
int op[maxn][maxn]; // 紀錄每個最好的操作
string str;

void print(int i, int j)
{
    if (i > j)
        return;
    if (i == j)
    {
        putchar(str[i]);
        return;
    }
    if (op[i][j] == 0)
    {
        putchar(str[i]);
        print(i + 1, j - 1);
        putchar(str[j]);
    }
    else if (op[i][j] == 1)
    {
        putchar(str[i]);
        print(i + 1, j);
        putchar(str[i]);
    }
    else
    {
        putchar(str[j]);
        print(i, j - 1);
        putchar(str[j]);
    }
}

int main()
{
    while (cin >> str)
    {
        memset(dp, 0, sizeof(dp));
        memset(op, 0, sizeof(op));

        int n = str.size();
        
        for (int l = 2; l <= n; ++l)
        {
            for (int i = 0; i < n; ++i)
            {
                int j = i + l - 1;
                if (j >= n)
                    break;
                
                if (str[i] == str[j])
                {
                    dp[i][j] = dp[i + 1][j - 1];
                    op[i][j] = 0;
                }
                else if (dp[i + 1][j] < dp[i][j - 1])
                {
                    dp[i][j] = dp[i + 1][j] + 1;
                    op[i][j] = 1;
                }
                else
                {
                    dp[i][j] = dp[i][j - 1] + 1;
                    op[i][j] = 2;
                }
            }
        }

        printf("%d ", dp[0][n - 1]);
        print(0, n - 1);
        puts("");
    }

    return 0;
}