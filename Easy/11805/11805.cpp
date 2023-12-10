#include <cstdio>

int main()
{
    int t;
    int n, k, p;
    scanf("%d", &t);
    for (int Case = 1; Case <= t; ++Case)
    {
        scanf("%d %d %d", &n, &k, &p);
        printf("Case %d: %d\n", Case, (k + p - 1) % n + 1);
    }
    return 0;
}