#include <cstdio>
#include <cmath>

int main()
{
    double n, p;
    while (scanf("%lf", &n) != EOF)
    {
        scanf("%lf", &p);
        printf("%.0lf\n", (pow(p, 1.0 / n)));
    }
    return 0;
}