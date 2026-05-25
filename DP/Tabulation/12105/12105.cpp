#include <bits/stdc++.h>
using namespace std;

/*
    這題需要一點greedy + dp
    1. 位數越長越好(如111大於99)
    2. 如果位數一樣，越左邊的數字越大越好(如911大於899)

    所以利用dp找出最長位數，利用for loop從9 ~ 0搜尋，
    優先把最大的數字擺前面

    (其實這題是一種帶有狀態的二維完全背包問題，商品價值是1(增加長度))
*/

int n, m;
// 每個數字需要幾根火柴
int need[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
// dp[i][j] 
// -> 在剩下i根火柴，目前餘數是j時，最多還能再往後加幾個位數，
//    並且保證最終整個整數可以被m整除
// dp[i][j] == -1 -> 沒有答案
int dp[105][3005];
// p[i][j] -> 狀態(i, j)時，為了達到dp[i][j]的最大長度，(i, j)這一步應該填入哪個數字
// p[i][j] == -1 -> 沒有答案
// 用來找回答案
int p[105][3005];

int main()
{
    int testcase = 0;

    while (scanf("%d", &n) && n)
    {
        scanf("%d", &m);

        memset(dp, -1, sizeof(dp));
        memset(p, -1, sizeof(p));

        printf("Case %d: ", ++testcase);

        // 窮舉剩下的火柴數量
        for (int i = 0; i <= n; ++i)
        {
            // 窮舉當前前綴數字的餘數
            for (int j = 0; j < m; ++j)
            {
                int& currMaxLen = dp[i][j];

                // 邊界條件
                // 如果當前餘數已經是0
                // 此時可以選擇不再加數字，所以先設為0作為合法解
                // 否則整個dp表都是-1
                if (j == 0)
                    currMaxLen = 0;

                // 嘗試在目前數字後面加上數字d(優先從9開始試)
                for (int d = 9; d >= 0; --d)
                {
                    // 如果剩下的火柴夠擺放數字d
                    if (i >= need[d])
                    {
                        // 如果加上數字d，剩餘的火柴變成 i - need[d]
                        // 新的餘數會變成 (j * 10 + d) % m
                        int nextLen = dp[i - need[d]][(j * 10 + d) % m];
                        // 如果下一個狀態合法(nextLen >= 0)
                        // 且加上d之後的總位數nextLen + 1 > currMaxLen
                        if (nextLen >= 0 && (nextLen + 1) > currMaxLen)
                        {
                            currMaxLen = nextLen + 1;
                            p[i][j] = d;
                        }
                    }
                }
            }
        }

        // 不存在合法解
        if (p[n][0] < 0)
            printf("-1\n");
        else
        {
            // 一開始有n根火柴，餘數為0
            int i = n, j = 0;
            for (int d = p[i][j]; d >= 0; d = p[i][j])
            {
                printf("%d", d);

                i -= need[d]; // 扣除當前用掉的火柴
                j = (j * 10 + d) % m; // 算新的餘數
            }
            puts("");
        }
    }

    return 0;
}