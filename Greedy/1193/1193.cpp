#include <bits/stdc++.h>
using namespace std;

/*
    只能在x軸上蓋雷達站，雷達站固定半徑為d
    問最少要蓋幾個雷達站才能涵蓋所有點
*/

const int maxn = 1005;

struct Island
{
    int x, y;
};

struct Segment
{
    double l, r;
};

Island islands[maxn];
Segment segs[maxn];

int main()
{
    int testcase = 0;

    int n, d;
    while (scanf("%d %d", &n, &d))
    {
        if (n == 0 && d == 0)
            break;
        
        int maxY = 0;

        for (int i = 0; i < n; ++i)
        {
            scanf("%d %d", &islands[i].x, &islands[i].y);

            maxY = max(maxY, islands[i].y);
        }

        printf("Case %d: ", ++testcase);

        // 最大的Y超過半徑，不可能可以涵蓋
        if (maxY > d)
        {
            printf("-1\n");
            continue;
        }

        /*
            以該點為圓心，畫半徑為d的圓
            此時在圓的範圍之內與該點的距離都 <= d
            所以求該圓與x軸的交點區間
            就是能夠蓋在x軸上能覆蓋到該點的範圍區間
        */
        for (int i = 0; i < n; ++i)
        {
            // 該點p(x, y)到x軸的垂直距離是y，
            // 最遠與x軸的距離為d
            // 所以可以利用畢氏定理
            // 求出該交點區間為 d - sqrt(d^2 - y^2) ~ d + sqrt(d^2 - y^2)
            // 看推導.png
            double dx = sqrt(d * d - islands[i].y * islands[i].y);
            segs[i].l = islands[i].x - dx;;
            segs[i].r = islands[i].x + dx;
        }

        // 到這邊問題轉變成找到最少點能夠覆蓋所有線段

        // 先照右端點由小到大，再照左端點由小到大排序
        sort(segs, segs + n, [](Segment& a, Segment& b) {
            if (a.r == b.r)
                return a.l < b.l;
            return a.r < b.r;
        });

        // 永遠安插新的點在線段的右端點
        // 如果目前涵蓋不到就繼續插新的點
        double curr = -0x3f3f3f3f;
        int res = 0;
        for (int i = 0; i < n; ++i)
        {
            if (curr < segs[i].l)
            {
                curr = segs[i].r;
                ++res;
            }
        }

        printf("%d\n", res);
    }

    return 0;
}