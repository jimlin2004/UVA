#include <cstdio>
#include <cmath>

//簡單幾何題
//正n邊形->一個等腰三角形的圓心角->360 / n
//再用(1/2) * a b sin(圓心角)即可解

const double pi = 3.14159265358979323846;

int main()
{
    double r, n;
    while (scanf("%lf %lf", &r, &n) != EOF)
    {
        double radians = (360.0 / n) * pi / 180.0;
        double totalArea = ((r * r * sin(radians)) / 2) * n;
        printf("%.3lf\n", totalArea);
    }
    return 0;
}