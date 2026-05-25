#include <bits/stdc++.h>
using namespace std;


/*
題意:
    給定多個塔需要的禮物數量，相鄰的塔之間不能有重複的禮物，問最少需要多少種禮物

首先如果是偶數的塔，那麼答案一定是兩兩個塔的最大和(因為i可以直接用i - 2的禮物以此類推)
如果是奇數個塔的話，需要對答案二分搜
問題在於怎麼檢查m個禮物能不能分完
答案是神奇的greedy

首先如果我們利用第一個塔需要的禮物數量將m分成左右兩半
( 也就是 第1種 第2種 ... | ... 第m種 總共m種禮物 )
然後第一個塔左邊禮物全部拿走

之後觀察由於塔的數量是奇數的時候，從1開始，最後一個塔一定是奇數
所以為了盡量讓第一個塔與最後一個塔不會拿到重複的禮物
我們規定
奇數編號塔從右邊開始拿禮物
偶數編號塔從左邊開始拿禮物

這樣就能讓最後一個塔與第一個塔最有可能不會有重複的禮物
(因為最後一個塔是奇數，且優先拿右邊)
具體做法看下方
*/

#define maxn 100005

int need[maxn];
int Left[maxn]; // 第i個塔拿左邊禮物的個數
int Right[maxn]; // 第i個塔拿右邊禮物的個數
int n;

bool check(int m)
{
    // 以第一個塔需要的禮物數為界分成左右兩邊
    int L = need[1];
    int R = m - need[1];

    // 第一個塔全拿左邊
    Left[1] = need[1];
    Right[1] = 0;

    for (int i = 2; i <= n; ++i)
    {
        if (i % 2 == 0) // 偶數從左邊拿
        {
            Left[i] = min(need[i], L - Left[i - 1]);
            Right[i] = need[i] - Left[i]; // 左邊拿完不夠就拿右邊
        }
        else // 奇數從右邊拿
        {
            Right[i] = min(need[i], R - Right[i - 1]);
            Left[i] = need[i] - Right[i]; // 右邊拿完不夠就拿左邊
        }
    }

    // 判斷最後一個塔有沒有拿到左邊的禮物
    return Left[n] == 0;
}

int main()
{
    while (scanf("%d", &n) != EOF && n)
    {
        for (int i = 1; i <= n; ++i)
            scanf("%d", &need[i]);
        
        if (n == 1)
        {
            printf("%d\n", need[1]);
            continue;
        }

        need[n + 1] = need[1]; // 最後一格多放變成循環array
        int l = 0, r = 0x3f3f3f3f;
        for (int i = 1; i <= n; ++i)
            l = max(l, need[i] + need[i + 1]);
        
        if (n % 2 == 1)
        {
            while (l < r)
            {
                int mid = (l + r) >> 1;
                if (check(mid))
                    r = mid;
                else
                    l = mid + 1;
            }
            printf("%d\n", l);
        }
        else
        {
            // 如果偶數個塔直接回傳兩兩最大和
            printf("%d\n", l);
        }
    }

    return 0;
}