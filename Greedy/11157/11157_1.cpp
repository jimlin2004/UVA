#include <bits/stdc++.h>
using namespace std;

#define maxn 105

struct Stone
{
    char type;
    int pos;
};

Stone stones[maxn];
bool used[maxn];

bool check(int maxLen, int N, int D)
{
    memset(used, 0, sizeof(used));

    // 需要來回
    // 當作從起點走兩次
    for (int t = 0; t < 2; ++t)
    {
        int i = 0;
        int last = 0;
        int prev = 0;
        while (stones[last].pos < D)
        {
            if (i > N)
                return false;
            if (used[i]) // 這顆石頭已經消失了
            {
                ++i;
            }
            else if (stones[i].pos - prev <= maxLen) // 能到最遠才跳就到最遠那顆
            {
                last = i;
                ++i;
            }
            else // 一定要跳，沒有可能的石頭了
            {
                if (stones[last].pos == prev)
                    return false;
                if (stones[last].type == 'S')
                    used[last] = true;
                prev = stones[last].pos;
            }
        }
    }

    return true;
}

int main()
{
    int T;
    scanf("%d", &T);

    int testcase = 0;

    while (T--)
    {
        int N, D;
        scanf("%d %d", &N, &D);

        // 起點放一顆大石頭
        stones[0].type = 'B';
        stones[0].pos = 0;

        for (int i = 1; i <= N; ++i)
            scanf(" %c-%d", &stones[i].type, &stones[i].pos);
        
        // 終點放一顆大石頭
        stones[N + 1].type = 'B';
        stones[N + 1].pos = D;
        
        N += 2;

        // 二分搜答案
        int l = 0, r = D;
        while (l + 1 < r)
        {
            int mid = (l + r) >> 1;
            if (check(mid, N, D))
                r = mid;
            else
                l = mid;
        }

        printf("Case %d: %d\n", ++testcase, r);
    }

    return 0;
}