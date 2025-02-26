#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

/*
    很神奇的題目
    看題目就知道沒有懸念用二分法搜答案
    但要求輸出分數
    做法是暴搜分母
    分母一定是 1 ~ n
    為什麼
    因為分母最大一定是n個幫派的範圍都有交集，
    整個線段連起來
    此時最好分法就是(線段長) / (幫派數)
    知道這件事
    就可以利用二分搜出來的ans = p / q
    暴搜q，移項得到p
    保留最接近ans的分數 p_r / q_r即為答案
*/

#define maxn 100005

struct Segment
{
    double l, r;
    bool operator < (const Segment& other) const
    {
        if (l == other.l)
            return r < other.r;
        return l < other.l;
    }
};

Segment segments[maxn];
int n;

// 基本線性掃描len能不能分
bool check(double len)
{
    double pos = 0;
    for (int i = 0; i < n; ++i)
    {
        if (pos < segments[i].l)
                pos = segments[i].l;
        if (pos + len > segments[i].r)
            return false;
        pos += len;
    }
    return true;
}

int main()
{
    while (scanf("%d", &n) != EOF)
    {
        double R = 0x3f3f3f3f;
        for (int i = 0; i < n; ++i)
        {
            scanf("%lf %lf", &segments[i].l, &segments[i].r);
            R = min(R, segments[i].r - segments[i].l);
        }
        sort(segments, segments + n);
        double L = 0;
        while (R - L > 1e-9)
        {
            double mid = (L + R) / 2;
            if (check(mid))
                L = mid;
            else
                R = mid;
        }
        // 神奇的小數轉分數
        int rp = 0, rq = 1;
        for (int q = 1; q <= n; ++q)
        {
            int p = round(q * L);
            if (fabs(((double)p / q) - L) < fabs(((double)rp / rq) - L))
            {
                rp = p;
                rq = q;
            }
        }
        printf("%d/%d\n", rp, rq);
    }
    return 0;
}
