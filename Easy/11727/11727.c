#include <stdio.h>

int main()
{
    int T, t;
    int x, y, z;
    scanf("%d", &T);
    for (t = 1; t <= T; ++t)
    {
        scanf("%d %d %d", &x, &y, &z);
        if ((y > x && x > z) || (y < x && x < z))
            printf("Case %d: %d\n", t, x);
        else if ((x > y && y > z) || (x < y && y < z))
            printf("Case %d: %d\n", t, y);
        else
            printf("Case %d: %d\n", t, z);
    }
    return 0;
}