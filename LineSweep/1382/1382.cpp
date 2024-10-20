#include <cstdio>
#include <algorithm>
using namespace std;

/*
看推導.png

枚舉加上掃描線法
枚舉的部分比較好想
就是枚舉y(水平線)，在固定水平線的時候只要找到長方形的左邊與右邊
而垂直線的找法就需要用掃描線法
為此我們創造出三個陣列left[]，on[]，on2[]，三陣列的定義看下方
至此我們找的長方形答案在max(left[j] - left[i] + on2[j] + on[i])
其中i < j
同時j是當前我們掃描到的垂直線j
所以在掃描的過程中需要維護最好的垂直線i具有max(on[i] - left[i])的值
(
    因為max(left[j] - left[i] + on2[j] + on[i])的j是現在枚舉的
    需要的是最好的on[i] - left[i]
)

另外當i != 0時left[i] = left[i - 1] + on2[i - 1] - on[i - 1]
這是因為on2[i - 1] - on[i - 1]可以得到垂直線i - 1在y1與y2上的點個數
*/

#define maxn 105

struct Point
{
    int x, y;
};

Point points[maxn];
int n;
//所有點的y座標
int Y[maxn]; 
//在垂線i上且在水平線y1, y2之間但不在y1, y2線上的點個數
int on[maxn]; 
//在垂線i上且在水平線y1, y2之間且包含在y1, y2線上的點個數
int on2[maxn];
//在垂線i左邊且在水平線y1, y2上的點個數
int left[maxn];

int solve()
{
    //將points[]以x由小到大排序
    sort(points, points + n, [&](const Point& a, const Point& b) {
        return a.x < b.x;
    });
    //將Y[]由小到大排序
    sort(Y, Y + n);
    //去掉重複的y
    int yLen = unique(Y, Y + n) - Y;
    //只有最多兩個水平線，那答案就是全部的點
    if (yLen <= 2)
        return n;
    int res = 0;

    //枚舉兩條水平線
    for (int y1Index = 0; y1Index < yLen; ++y1Index)
    {
        for (int y2Index = y1Index + 1; y2Index < yLen; ++y2Index)
        {
            int y1 = Y[y1Index];
            int y2 = Y[y2Index];
            //開始計算left[]以及on[]還有on2[]
            //cnt = 垂線的數量(即有多少個不同的x座標)
            int cnt = 0;
            //垂線由左到右掃描
            for (int i = 0; i < n; ++i)
            {
                //出現新的垂線
                if (i == 0 || points[i].x != points[i - 1].x)
                {
                    ++cnt;
                    on[cnt] = on2[cnt] = 0;
                    left[cnt] = (cnt == 0) ? 0 : left[cnt - 1] + on2[cnt - 1] - on[cnt - 1];
                }
                if (y1 < points[i].y && points[i].y < y2)
                    ++on[cnt];
                if (y1 <= points[i].y && points[i].y <= y2)
                    ++on2[cnt];
            }

            //如果最多只有兩條垂線，那答案就是n(全部選)
            if (cnt <= 2)
                return n;
            //紀錄最好的垂直線i，有最大的max(on[i] - left[i])
            int M = 0;
            //枚舉垂直線j
            for (int j = 1; j <= cnt; ++j)
            {
                //維護最好的答案
                res = max(res, left[j] + on2[j] + M);
                //維護最好的垂直線i
                M = max(M, on[j] - left[j]);
            }
        }
    }
    return res;
}

int main()
{
    int Case = 0;
    while (scanf("%d", &n) && n)
    {
        for (int i = 0; i < n; ++i)
        {
            scanf("%d %d", &points[i].x, &points[i].y);
            Y[i] = points[i].y;
        }
        printf("Case %d: %d\n", ++Case, solve());
    }
    return 0;
}