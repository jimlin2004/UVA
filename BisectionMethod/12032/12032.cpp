#include <bits/stdc++.h>
using namespace std;

/*
    題意:
        猴子起跳，每次要到竹子的竹節上，如果跳的距離跟猴子目前的力氣值一樣
        猴子的力氣值會減一，問最小需要多少力氣值?

    可以用倒過來O(n)維護答案
    但我直接正著用二分搜答案了O(n log k)
*/

int n;
int heights[100005];

// 能跳就跳，否則會增加距離
bool check(int k)
{
    int curr = 0;

    for (int i = 0; i < n; ++i)
    {
        if (heights[i] - curr > k)
            return false;
        else if (heights[i] - curr == k)
            --k;
        curr = heights[i];
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
        scanf("%d", &n);
        for (int i = 0; i < n; ++i)
            scanf("%d", &heights[i]);
        
        int l = 0, r = 0x3f3f3f3f;
        while (l + 1 < r)
        {
            int mid = (l + r) >> 1;
            if (check(mid))
                r = mid;
            else
                l = mid;
        }

        printf("Case %d: %d\n", ++testcase, r);
    }

    return 0;
}