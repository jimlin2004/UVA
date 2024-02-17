#include <cstdio>

int main()
{
    int t;
    int n, m;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d %d", &n, &m);
        printf("%d\n", (n / 3) * (m / 3));
    }
    return 0;
}