#include <bits/stdc++.h>
using namespace std;

/*
    一條數線上
    每個加油站x，能負責[x - r, x + r]的範圍
    要選最少間加油站能夠涵蓋[0, L]的範圍

    所以直接greedy的最小線段覆蓋問題就行了
*/

struct Seg
{
    int l, r;
};

Seg segs[10005];

int main()
{
    int L, G;
    while (scanf("%d %d", &L, &G))
    {
        if (L == 0 && G == 0)
            break;
        
        for (int i = 0; i < G; ++i)
        {
            int x, r;
            scanf("%d %d", &x, &r);
            segs[i] = {x - r, x + r};
        }

        // 照左端點排序
        sort(segs, segs + G, [](Seg& a, Seg& b) {
            return a.l < b.l;
        });

        int curr = 0;

        int res = 0;
        for (int i = 0; i < G;)
        {
            if (curr < segs[i].l)
            {
                res = -1;
                break;
            }

            int maxR = -0x3f3f3f3f;
            // 選可以接的之中右端點最遠的那一條
            while (i < G && segs[i].l <= curr)
            {
                maxR = max(maxR, segs[i].r);
                ++i;
            }
            curr = maxR;
            ++res;
            if (curr >= L)
                break;
        }

        if (curr < L)
            res = -1;

        if (res == -1)
            puts("-1");
        else
            printf("%d\n", G - res);
    }

    return 0;
}