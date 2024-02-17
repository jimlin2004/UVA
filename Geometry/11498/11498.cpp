#include <cstdio>

int main()
{
    int q;
    int ox, oy;
    int x, y;
    while (scanf("%d", &q) && q)
    {
        scanf("%d %d", &ox, &oy);
        while (q--)
        {
            scanf("%d %d", &x, &y);
            x -= ox;
            y -= oy;
            if ((x == 0) || (y == 0))
                puts("divisa");
            else if ((x > 0) && (y > 0))
                puts("NE");
            else if ((x < 0) && (y > 0))
                puts("NO");
            else if ((x < 0) && (y < 0))
                puts("SO");
            else if ((x > 0) && (y < 0))
                puts("SE");
        }
    }
    return 0;
}