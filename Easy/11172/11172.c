#include <stdio.h>

int main()
{
    int i, n;
    long long int a, b, res;
    scanf("%d", &n);
    for (i = 0; i < n; ++i)
    {
        scanf("%lld %lld", &a, &b);
        res = a - b;
        if (res < 0)
            puts("<");
        else if (res > 0)
            puts(">");
        else
            puts("=");
    }
    return 0;
}