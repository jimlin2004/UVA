#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

#define maxn 505
#define eps 1e-9

const double PI = acos(-1);

/*
    要找到一個方向，使射手能夠射到最多的線段
    做法是用極角掃描後排序，
    將極角當作數線上的數值，如此從線段左邊與右邊的極角
    就能夠成數線上的線段
    問題就轉變成找最多重疊線段數
    方法就是在線段左邊設定+1，右邊設定-1
    一路計算維護最大值O(n)即可
*/

struct Line
{
    double x1, y1, x2, y2;
};

struct Point
{
    double radians;
    int k;
    bool operator < (const Point& other) const
    {
        //細節，當點的位置一樣時，+1的那一端要先出來，否則會少算
        if (fabs(this->radians - other.radians) > eps)
            return this->radians < other.radians;
        return this->k > other.k; // +1先出來
    }
};

Line lines[maxn];
//點是邊的兩倍
Point points[maxn * 2];

int main()
{
    int n;
    while (scanf("%d", &n) && n)
    {
        for (int i = 0; i < n; ++i)
            scanf("%lf %lf %lf %lf", &lines[i].x1, &lines[i].y1, &lines[i].x2, &lines[i].y2);
        double posX, posY;
        scanf("%lf %lf", &posX, &posY);
        int m = 0;
        for (int i = 0; i < n; ++i)
        {
            double l = atan2(lines[i].y1 - posY, lines[i].x1 - posX);
            double r = atan2(lines[i].y2 - posY, lines[i].x2 - posX);
            // 保持r >= l
            if (l > r)
                swap(l, r);
            // 細節: 由於atan2，當r - l >= PI時會發生-PI <= l < r <= pi
            // 所以要拆成[-PI, l]與[r, PI]
            // 看推導1.png
            if (r - l >= PI)
            {
                // 這裡放[-PI, l]
                points[m].radians = -PI;
                points[m++].k = 1;
                points[m].radians = l;
                points[m++].k = -1;
                // [r, PI交給後面的程式]
                l = r;
                r = PI;
            }
            points[m].radians = l;
            points[m++].k = 1;
            points[m].radians = r;
            points[m++].k = -1;
        }
        sort(points, points + m);
        // 掃描找最多線段重疊數量
        int res = -0x3f3f3f3f;
        int curr = 0;
        for (int i = 0; i < m; ++i)
        {
            curr += points[i].k;
            res = max(res, curr);
        }
        printf("%d\n", res);
    }
    
    return 0;
}
/*
3
0 0 10 0
0 1 10 1
0 2 10 2
0 -1
*/