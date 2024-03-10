#include <cstdio>
#include <cmath>
using namespace std;

//物理向量分力題目

int main()
{
    int t;
    scanf("%d", &t);
    int Case = 0;
    while (t--)
    {
        double d, v, u;
        scanf("%lf %lf %lf", &d, &v, &u);
        /*
            1. 水流速 == 0 -> 兩個路徑會變一致
            2. 船速   == 0 -> 根本不會動
            3. 水流速 == 船速 -> 船沒辦法抵銷水流
            -> 無法測量
        */
        printf("Case %d: ", ++Case);
        if (u == 0 || v == 0 || u <= v)
        {
            puts("can't determine");
        }
        else
        {
            double shortestPath = d / u;
            double shortestTime = d / sqrt(u * u - v * v);
            printf("%.3lf\n", shortestTime - shortestPath);
        }
    }
    return 0;
}