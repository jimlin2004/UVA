#include <stdio.h>

int main()
{
    int T;
    int a, b;
    int n;
    int i;
    scanf("%d", &T);
    for (i = 1; i <= T; ++i)
    {
        scanf("%d", &a);
        scanf("%d", &b);
        if ((a % 2) == 0)
            a += 1;
        if ((b % 2) == 0)
            b -= 1;
        n = (b - a) / 2 + 1;
        printf("Case %d: %d\n", i, ((a + b) * n) / 2);
    }
    return 0;
}