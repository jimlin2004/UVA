#include <bits/stdc++.h>
using namespace std;


int main()
{
    double x[10];
    double y[10];

    // 用平行四邊形的座標 相加會相等的定理(向量)
    while (scanf("%lf %lf %lf %lf %lf %lf %lf %lf", &x[1], &y[1], &x[2], &y[2], &x[3], &y[3], &x[4], &y[4]) != EOF)
    {
        if (x[1] == x[3] && y[1] == y[3])
            printf("%.3lf %.3lf\n", x[2] + x[4] - x[1], y[2] + y[4] - y[1]);
        else if (x[1] == x[4] && y[1] == y[4])
            printf("%.3lf %.3lf\n", x[2] + x[3] - x[1], y[2] + y[3] - y[1]);
        else if (x[2] == x[3] && y[2] == y[3])
            printf("%.3lf %.3lf\n", x[1] + x[4] - x[2], y[1] + y[4] - y[2]);
        else
            printf("%.3lf %.3lf\n", x[1] + x[3] - x[2], y[1] + y[3] - y[2]);
    }

    return 0;
}