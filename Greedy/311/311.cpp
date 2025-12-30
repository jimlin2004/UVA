#include <bits/stdc++.h>
using namespace std;

int cnt[10];

/*
    策略:
    先從大的開始放: 6x6 -> 5x5 -> 4x4 -> 3x3
    剩下2 x 2跟1 x 1的優先塞多出來的空位
*/

int main()
{
    while (1)
    {
        int total = 0;
        for (int i = 1; i <= 6; ++i)
        {
            scanf("%d", &cnt[i]);
            total += cnt[i];
        }

        if (total == 0)
            break;
        
        // 首先6x6的一定只能自己一箱，所以需要的箱子數先加上去
        int res = cnt[6];
        int oneCnt = 0; // 當前多出來的1x1空位
        int twoCnt = 0; // 當前多出來的2x2空位

        // 5x5的基本佔滿空間，只會多出11個1x1的空位
        res += cnt[5];
        oneCnt += cnt[5] * 11;

        // 4x4的放完會多5個2x2的空位
        // (先不算到1x1，因為塞完2x2的之後可以轉給1x1的用)
        res += cnt[4];
        twoCnt += cnt[4] * 5;

        // 6x6的空間可以放4個3x3的剛好塞滿
        res += cnt[3] / 4;
        cnt[3] %= 4; // 算多出幾個3x3的還沒塞
        if (cnt[3] == 1) // 6x6的空間只塞一個3x3的
        {
            ++res;
            // 會多出 5個2x2，7個1x1
            twoCnt += 5;
            oneCnt += 7;
        }
        else if (cnt[3] == 2) // 6x6的空間只塞兩個3x3的
        {
            ++res;
            // 會多出 3個2x2，6個1x1
            twoCnt += 3;
            oneCnt += 6;
        }
        else if (cnt[3] == 3) // 6x6的空間只塞3個3x3的
        {
            ++res;
            // 會多出 1個2x2，5個1x1
            twoCnt += 1;
            oneCnt += 5;
        }

        // 如果原本多出來的空位不夠塞2x2的
        if (twoCnt < cnt[2])
        {
            // 那就要算要多幾個箱子
            cnt[2] -= twoCnt;
            res += cnt[2] / 9; // 6x6的箱子可以塞9個2x2的
            cnt[2] %= 9;
            if (cnt[2] > 0) // 如果最後一箱塞2x2沒塞滿
            {
                ++res; // 多一箱
                oneCnt += (36 - cnt[2] * 4); // 算多出幾個1x1的
            }
        }
        else // 原本的空間就夠塞了
            oneCnt += (twoCnt - cnt[2]) * 4; // 多出來的2x2空間轉成多出幾個1x1的空間

        // 如果原本的多出空間不夠塞
        if (oneCnt < cnt[1])
        {
            cnt[1] -= oneCnt;
            res += cnt[1] / 36; // 看要多幾箱
            cnt[1] %= 36;
            if (cnt[1] > 0) // 最後一箱可能沒塞滿
                ++res;
        }
        //else 不用多箱子，就不用做其他事

        printf("%d\n", res);
    }

    return 0;
}