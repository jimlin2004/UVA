#include <cstdio>
#include <cmath>

//求三角形內接圓半徑

int main()
{
    double a, b, c;
    while (scanf("%lf %lf %lf", &a, &b, &c) != EOF)
    {
        double s = (a + b + c) / 2.0;
        if (s == 0.0)
            printf("The radius of the round table is: 0.000\n");
        else
        {
            double area = sqrt(s * (s - a) * (s - b) * (s - c));
            double r = 2 * area / (a + b + c);
            printf("The radius of the round table is: %.3lf\n", r);
        }
    }
    return 0;
}