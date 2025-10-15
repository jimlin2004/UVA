#include <bits/stdc++.h>
using namespace std;

/*
    題意是要每次增加建築時
    如果看的到該建築的天際線
    就要加起來，最後輸出總計長度

    線段樹 + 區間修改
*/

#define maxn 100005

int ST[maxn << 2];
int tag[maxn << 2];

int res = 0;

void pushDown(int l, int r, int i)
{
    // 葉節點不用往下
    if (tag[i] && l != r)
    {
        tag[i * 2] = tag[i * 2 + 1] = tag[i];
        ST[i * 2] = ST[i * 2 + 1] = ST[i];
        tag[i] = 0;
    }
}

void update(int ql, int qr, int l, int r, int i, int h)
{
    // 現在的值比h大，就不用計算與更新
    // 但是需要用tag[i]是否有值才知道這個節點的ST值是由設定而來
    // 還是子樹pullUp而來，要是設定而來的才能減枝
    if (tag[i] && ST[i] > h)
        return;

    if (ql <= l && r <= qr)
    {
        // 這一個區間要修改
        if (ST[i] <= h)
        {
            ST[i] = h;
            tag[i] = h;

            res += r - l + 1;
            return;
        }
    }

    pushDown(l, r, i);

    int mid = (l + r) >> 1;
    if (ql <= mid)
        update(ql, qr, l, mid, i * 2, h);
    if (mid < qr)
        update(ql, qr, mid + 1, r, i * 2 + 1, h);
    
    ST[i] = max(ST[i * 2], ST[i * 2 + 1]);
}

int main()
{
    int T;
    while (scanf("%d", &T) && T)
    {
        while (T--)
        {
            res = 0;
            memset(ST, 0, sizeof(ST));
            memset(tag, 0, sizeof(tag));

            int n;
            scanf("%d", &n);

            for (int i = 0; i < n; ++i)
            {
                int l, r, h;
                scanf("%d %d %d", &l, &r, &h);

                // 這一題給的建築是[l, r)的
                update(l, r - 1, 0, maxn - 1, 1, h);
            }

            printf("%d\n", res);
        }
    }

    return 0;
}