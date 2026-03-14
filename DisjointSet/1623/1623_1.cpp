#include <bits/stdc++.h>
using namespace std;

/*
    題目作法: 貪婪
    目標是預測第i個湖會下雨的時候，在上一次第i個湖被填滿的日子到下雨的今天之間找到第一天不會下雨的是哪天
    這樣的要求會想到用set進行二分搜找，
    能過，但事實上10^6這樣的資料用O(m log m)有點碰運氣
*/

#define maxn 1000005

// lastFullDay[i] -> 第i個湖最近被填滿的天數
// 由於一開始都是滿的，設為第0天
int lastFullDay[maxn];
// 用來搜尋沒有下雨的天數
set<int> noRainDay;
// 用來標記答案用的
int res[maxn];

// 天氣預報
int predicted[maxn];

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
        noRainDay.clear();
        memset(res, 0, sizeof(res));

        for (int i = 1; i <= m; ++i)
        {
            scanf("%d", &predicted[i]);
        }

        bool ok = true;

        for (int i = 1; i <= m; ++i)
        {
            if (predicted[i] == 0)
                noRainDay.insert(i);
            else
            {
                // 找到第rain的湖上一次被填滿的日子到今天之間第一個沒下雨的是哪天
                auto it = noRainDay.lower_bound(lastFullDay[predicted[i]]);
                if (it == noRainDay.end())
                {
                    ok = false;
                    break;
                }
                // 沒下雨的這一天要先喝完水
                res[*it] = predicted[i];
                noRainDay.erase(it);
                // 湖被重新填滿
                lastFullDay[predicted[i]] = i;
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