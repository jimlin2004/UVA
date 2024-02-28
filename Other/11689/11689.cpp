#include <cstdio>

int main()
{
    int t;
    scanf("%d", &t);
    int e, f, c;
    while (t--)
    {
        scanf("%d %d %d", &e, &f, &c);
        e += f;
        int newEmpty;
        int res = 0;
        while (e >= c)
        {
            newEmpty = e / c;
            res += newEmpty;
            e %= c;
            e += newEmpty;
        }
        printf("%d\n", res);
    }
    return 0;
}