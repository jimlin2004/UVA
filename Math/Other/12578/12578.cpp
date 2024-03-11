#include <cstdio>
#include <cmath>

/*
超級簡單數學
*/

const double pi = acos(-1);

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        double len;
        scanf("%lf", &len);
        double height = len * 0.6;
        double r = len / 5.0;
        double circleArea = r * r * pi;
        printf("%.2lf %.2lf\n", circleArea, len * height - circleArea);
    }
    return 0;
}