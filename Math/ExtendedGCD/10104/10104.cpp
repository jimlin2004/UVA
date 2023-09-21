#include <cstdio>

int exgcd(int a, int b, int& x, int& y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }

    int gcd = exgcd(b, a % b, x, y);
    int y1 = y;
    y = x - (a / b) * y;
    x = y1;
    return gcd;
}

int main()
{
    int x, y;
    int a, b;
    int gcd;
    while (scanf("%d %d", &a, &b) != EOF)
    {
        gcd = exgcd(a, b, x, y);
        printf("%d %d %d\n", x, y, gcd);
    }
    return 0;
}