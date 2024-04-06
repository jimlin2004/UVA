#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

/*
經典DivideAndConquer
考慮三種case:
    1. 最短距離在左邊
    2. 最短距離在右邊
    3. 最短距離橫跨兩邊

    一路divide下去後
    可以知道左右兩邊的個別最小距離
    考慮橫跨中間的點:
        在確定左右兩邊的min dl, dr
        取d = min(dl, dr)
        左右兩邊的中線座標 midLine = (points[mid] + points[mid + 1] / 2)
        則橫跨中間的點只需要考慮
        左半邊point.x > midLine - d
        右半邊point.x < midLine + d
        也就是以midLine為中線，寬度為2d的長方形
        只有此長方形的點才有可能比原本的dl, dr小
    最後combine起來即為答案
    O(nlogn) -> 用The Master Theorem可證
*/

#define maxn 10005

struct Point
{
    double x, y;
    bool operator<(const Point& other) const
    {
        if (this->x == other.x)
            return this->y < other.y;
        return this->x < other.x;
    }

    double operator-(const Point& other) const
    {
        return sqrt((this->x - other.x) * (this->x - other.x) + (this->y - other.y) * (this->y - other.y));
    }
};

Point points[maxn];

double combine(double d, int mid, int l, int r)
{
    double minDis = d;
    double midLine = (points[mid].x + points[mid + 1].x) / 2.0;
    for (int i = mid; i >= l && (points[i].x > midLine - d); --i)
    {
        for (int j = mid + 1; j <= r && (points[j].x < midLine + d); ++j)
        {
            minDis = min(minDis, points[i] - points[j]);
        }
    }
    return minDis;
}

double divide(int l, int r)
{
    if (l >= r)
        return 0x3f3f3f3f * 1.0;
    int mid = (l + r) / 2;
    double dl = divide(l, mid);
    double dr = divide(mid + 1, r);
    return combine(min(dl, dr), mid, l, r);
}

int main()
{
    int n;
    while (scanf("%d", &n) && n)
    {
        for (int i = 0; i < n; ++i)
            scanf("%lf %lf", &points[i].x, &points[i].y);
        sort(points, points + n);
    
        double minDis = divide(0, n - 1);
        if (minDis >= 10000.0)
            puts("INFINITY");
        else
            printf("%.4lf\n", minDis);
    }
    return 0;
}