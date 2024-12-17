#include <cstdio>
#include <cmath>
using namespace std;

// 這題浮點值非常敏感，eps不同就可能有誤差或超時
#define eps 1e-6

/*
    看 推導.png
    考數學的推導以及用二分搜做數值分析
*/

int main()
{
    double L, D, C;
    while (scanf("%lf %lf %lf", &L, &D, &C) != EOF)
    {
        if (L < 0 && D < 0 && C < 0)
            break;
        // 這裡一定要特判，否則會超時
        if (D == 0 || C == 0)
        {
            puts("0.000");
            continue;
        }
        // Lp是膨脹後的長度
        double Lp = (1 + D * C) * L;
        // 因為推導時的計算，L、Lp都 / 2會比較方便
        L /= 2;
        Lp /= 2;
        // 搜的是半徑
        // l永遠不會小於L，r設成一個無限大的值(夠大的值)
        double l = L, r = 1e10;
        double mid;
        while (r - l > eps)
        {
            mid = (l + r) / 2;
            // 如果L / mid比較小，那就要調小mid
            if (sin(Lp / mid) > L / mid)
                r = mid;
            else
                l = mid;
        }
        printf("%.3lf\n", l - l * cos(Lp / l));
    }
    return 0;
}