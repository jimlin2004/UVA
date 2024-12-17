#include <iostream>
#include <cstring>
using namespace std;

/*
    找字串可以切出最少幾段，每段都是迴文
    O(n ^ 2)建迴文表，O(n ^ 2)找答案
*/

#define maxn 1005

string str;
//dp[i][j] -> 字串i到j是不是迴文
bool dp[maxn][maxn];
//cnt[i] -> 到i結尾最少切出多少每段都是迴文
int cnt[maxn];

int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        cin >> str;
        memset(dp, 0, sizeof(dp));
        memset(cnt, 0x3f, sizeof(cnt));

        //很樸素的dp O(n^2)處理i~j是不是迴文
        //先枚舉長度再枚舉起點
        for (int l = 1; l <= str.size(); ++l)
        {
            for (int i = 0; i + l - 1 < str.size(); ++i)
            {
                int j = i + l - 1;
                if (i == j)
                {
                    dp[i][j] = true;
                }
                else if (l == 2)
                {
                    dp[i][j] = (str[i] == str[j]);
                }
                else
                {
                    if (str[i] == str[j])
                        dp[i][j] = dp[i + 1][j - 1];
                    else
                        dp[i][j] = false;
                }
            }
        }
        
        //以下dp也要O(n ^ 2)
        //初始化cnt[0] = 1; 因為第一個字自己一定是迴文，前面也沒人了
        cnt[0] = 1;
        for (int i = 1; i < str.size(); ++i)
        {
            //枚舉i之前有沒有j可以使字串j ~ i是迴文(j可以等於i，因為可能前面都湊不出來，但字串i = j的字母自己可以算1個迴文)
            for (int j = 0; j <= i; ++j)
            {
                //如果j ~ i是迴文
                if (dp[j][i])
                {
                    //若j > 0，此時試試看讓j ~ i自己一段，且與cnt[j - 1]去找答案是否更短
                    if (j > 0)
                        cnt[i] = min(cnt[i], cnt[j - 1] + 1); //cnt[i]試試看cnt[j - 1]加上j ~ i這一段有沒有比較短
                    else
                        cnt[i] = cnt[j]; //此時j ~ i相當於0 ~ i是迴文，那cnt[i]就等於1(即一段迴文)
                }
            }
        }
        //答案在cnt[str.size() - 1]
        printf("%d\n", cnt[str.size() - 1]);
    }
    return 0;
}

/*
3
racecar
fastcar
aaadbccb
*/