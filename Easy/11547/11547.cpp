#include <cstdio>
#include <cstdlib>

int main()
{
    int t;
    scanf("%d", &t);
    long long n;
    while (t--)
    {
        scanf("%lld", &n);
        n *= 567;
        n /= 9;
        n += 7492;
        n *= 235;
        n /= 47;
        n -= 498;
        printf("%d\n", abs((n % 100) / 10));
    }
    return 0;
}