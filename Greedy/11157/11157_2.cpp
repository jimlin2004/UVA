#include <bits/stdc++.h>
using namespace std;

#define maxn 105

struct Stone
{
    char type;
    int pos;
};

Stone stones[maxn];

int main()
{
    int T;
    scanf("%d", &T);

    int testcase = 0;

    while (T--)
    {
        int N, D;
        scanf("%d %d", &N, &D);

        // 起點放一個大石頭
        stones[0].type = 'B';
        stones[0].pos = 0;

        for (int i = 1; i <= N; ++i)
            scanf(" %c-%d", &stones[i].type, &stones[i].pos);
        
        // 終點放一顆大石頭
        stones[N + 1].type = 'B';
        stones[N + 1].pos = D;
        
        N += 2;

        // 想成兩隻青蛙一起從起點出發
        int f1 = 0;
        int f2 = 0;
        int res = 0;

        for (int i = 0; i < N; ++i)
        {
            // 如果是大石頭，沒有理由不跳上去(跳上去可以縮短與後續石頭的距離)
            if (stones[i].type == 'B')
            {
                // 兩隻都跳
                res = max({res, stones[i].pos - f1, stones[i].pos - f2});
                f1 = f2 = stones[i].pos;
            }
            else // 遇到小石頭，在後面的青蛙先跳
            {
                if (f1 < f2) // 第一隻青蛙先跳 
                {
                    res = max(res, stones[i].pos - f1);
                    f1 = stones[i].pos;
                }
                else
                {
                    res = max(res, stones[i].pos - f2);
                    f2 = stones[i].pos;
                }
            }
        }

        printf("Case %d: %d\n", ++testcase, res);
    }

    return 0;
}