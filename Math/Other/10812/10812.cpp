#include <cstdio>

/*
解聯立:
    x + y = a
    x - y = b
*/

int main()
{
    long long x, y, a, b;
    int t;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%lld %lld", &a, &b);
        if (b > a)
        {
            puts("impossible");
            continue;
        }
        if ((a + b) % 2 != 0)
        {
            puts("impossible");
            continue;
        }
        x = (a + b) / 2;
        y = a - x;
        printf("%lld %lld\n", x, y);
    }
    return 0;
}