#include <bits/stdc++.h>
using namespace std;

/*
    狀壓dp
    設定狀態0代表還沒打敗，1是已經打敗
    之後對應題目設計狀態轉移式
    詳細看下方
*/

const int maxn = 1 << 16;

long long dp[maxn]; // dp[state] -> 為該狀態時的方法數
int states[maxn]; // 目前state i可以打敗的robot是哪些人
char input[25];
int busters[25]; // 記著用busters[i]後可以打敗誰


int main()
{
    int T;
    scanf("%d", &T);

    int Case = 0;

    while (T--)
    {
        int n;
        scanf("%d", &n);
        getchar();

        memset(dp, 0, sizeof(dp));
        memset(states, 0, sizeof(states));
        memset(busters, 0, sizeof(busters));

        for (int i = 0; i <= n; ++i)
        {
            scanf("%s", input);

            int rb = 1; // 枚舉robot對應的bit
            for (int j = 0; j < n; ++j)
            {
                if (input[j] == '1')
                    busters[i] |= rb;
                rb <<= 1;
            }
        }

        states[0] = busters[0]; // 因為一開始用busters[0]，所以記著誰都還沒打倒前000...000可以打敗busters
        dp[0] = 1;

        int N = 1 << n;

        // 枚舉所有狀態
        for (int i = 0; i < N; ++i)
        {
            // 還沒殺的有(~i)，可以殺的有states[i]
            // 如i = 100 -> robot3已經打敗，(~i) = 011 -> 還有robot1、2要打敗
            // 所以做and就是還沒殺且可以殺的有哪些robots
            int todo = (~i) & states[i];

            int rb = 1; // 枚舉robot對應的bit
            for (int j = 1; j <= n; ++j)
            {
                if (todo & rb) // 如果robot可以打敗且還沒打敗
                {
                    dp[i | rb] += dp[i]; // 打敗rb，方法數加上去
                    states[i | rb] = states[i] | busters[j]; // 更新打敗rb後可以打敗誰
                }
                
                rb <<= 1;
            }
        }

        // 答案在都打敗的狀態，所以是111...1111 -> N - 1
        printf("Case %d: %lld\n", ++Case, dp[N - 1]);
    }

    return 0;
}