#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

//<Note> 題目範圍騙人，題目嚴格遞增，又最多只有26個字母
//       所以最大只到1+2+3+4+..+26 = 351

int dp[27][27][352] = {0};
//定義dp[i][l][s] -> 只使用前1~i小寫字母時的字串長度為l總值為s
//轉移式:
//由於第i個小寫字母可選可不選，所以
//dp[i][j][k] = dp[i - 1][j][k] + dp[i - 1][j - 1][k - i]
//邊界: dp[0][0][0] = 1

int main()
{
    int L, S;
    int Case = 1;

    dp[0][0][0] = 1;
    for (int i = 1; i <= 26; ++i)
    {
        for (int j = 0; j <= i; ++j)
        {
            for (int k = 0; k <= 351; ++k)
            {
                dp[i][j][k] = dp[i - 1][j][k];
                if (j && (k >= i))
                    dp[i][j][k] += dp[i - 1][j - 1][k - i];
            }
        }
    }

    while (scanf("%d %d", &L, &S) != EOF && (L + S))
    {
        printf("Case %d: ", Case++);
        if (L > 26 || S > 351)
            printf("0\n");
        else
            printf("%d\n", dp[26][L][S]);
    }
    return 0;
}