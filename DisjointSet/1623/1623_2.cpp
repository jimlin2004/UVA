#include <bits/stdc++.h>
using namespace std;

/*
    題目作法: 貪婪
    目標是預測第i個湖會下雨的時候，在上一次第i個湖被填滿的日子到下雨的今天之間找到第一天不會下雨的是哪天
    上一個做法是用set
    這裡改用並查集維護，能夠做到O(m * 阿卡曼反函數(m))
    具體做法看下方
*/

#define maxn 1000005

// lastFullDay[i] -> 第i個湖最近被填滿的天數
// 由於一開始都是滿的，設為第0天
int lastFullDay[maxn];
// 用來標記答案用的
int res[maxn];
// 並查集
int parent[maxn];
// 天氣預報
int predicted[maxn];

// 在這題的用法中，findRoot(x)可以當作找第x天以後(包含)最近沒下雨的是哪一天
int findRoot(int x)
{
    if (parent[x] == x)
        return x;
    return parent[x] = findRoot(parent[x]);
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n, m;
        scanf("%d %d", &n, &m);

        // 預設第0天是滿的
        memset(lastFullDay, 0, sizeof(lastFullDay));
        memset(res, 0, sizeof(res));

        for (int i = 1; i <= m; ++i)
        {
            scanf("%d", &predicted[i]);
        }

        // 貪婪地從右往左建並查集幫助搜尋沒下雨的天
        // 這邊假設第m + 1天不會下雨
        int lastNoRainDay = m + 1;
        parent[m + 1] = m + 1;
        // 這裡記得第0天也要給到DSU中
        for (int i = m; i >= 0; --i)
        {
            if (predicted[i] == 0 && i != 0)
            {
                lastNoRainDay = i;
            }
            parent[i] = lastNoRainDay;
        }
        
        bool ok = true;
        for (int i = 1; i <= m; ++i)
        {
            if (predicted[i] != 0)
            {
                int noRainDay = findRoot(lastFullDay[predicted[i]]);
                if (noRainDay >= i) // 搜不到
                {
                    ok = false;
                    break;
                }
                // 找到哪一天應該喝水
                res[noRainDay] = predicted[i];
                // 湖被重新填滿
                lastFullDay[predicted[i]] = i;
                // 因為noRainDay被用掉了，所以這個DSU要全部往後移
                // 概念是noRainDay不下雨的第一天就是findRoot(noRainDay + 1)的那一天(因為我們貪婪地由右往左建DSU)
                // 也就是因為noRainDay被用掉之後，下個最近沒下雨的天至少是一天後，所以直接用findRoot(noRainDay + 1)去找即可
                // 利用了DSU快速修正區間的優勢
                parent[noRainDay] = findRoot(noRainDay + 1);
            }
        }

        if (!ok)
            puts("NO");
        else
        {
            puts("YES");
            bool first = true;
            for (int i = 1; i <= m; ++i)
            {
                // 只有沒下雨的天要輸出
                if (predicted[i] == 0)
                {
                    if (first)
                        first = false;
                    else
                        putchar(' ');
                    printf("%d", res[i]);
                }
            }
            puts("");
        }
    }

    return 0;
}