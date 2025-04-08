#include <bits/stdc++.h>
using namespace std;

// 可參考leetcode 42
// 也能用另一種填油的想法(換湯不換藥)

#define maxn 1000005

int ceilings[maxn];
int floors[maxn];

// 左邊與右邊(都包含)算過來能填充的最高高度
int maxHL[maxn];
int maxHR[maxn];

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int n;

        scanf("%d", &n);

        for (int i = 1; i <= n; ++i)
            scanf("%d", &floors[i]);

        for (int i = 1; i <= n; ++i)
            scanf("%d", &ceilings[i]);

        // 找到最高的地板
        int maxF = 0;
        for (int i = 1; i <= n; ++i)
            maxF = max(maxF, floors[i]);
        
        // 將左右兩邊的界線設為最高地板
        floors[0] = maxF;
        floors[n + 1] = maxF;
        
        maxHL[0] = maxF;
        // 紀錄i的左邊最大(包含)
        for (int i = 1; i <= n; ++i)
        {
            maxHL[i] = min(max(maxHL[i - 1], floors[i]), ceilings[i]);
        }

        maxHR[n + 1] = maxF;
        // 紀錄i的右邊最大(包含)
        for (int i = n; i >= 1; --i)
        {
            maxHR[i] = min(max(maxHR[i + 1], floors[i]), ceilings[i]);
        }

        // 算能裝多少
        int res = 0;
        for (int i = 1; i <= n; ++i)
        {
            int height = min(maxHL[i], maxHR[i]);
            res += (height - floors[i]);
        }

        printf("%d\n", res);
    }

    return 0;
}