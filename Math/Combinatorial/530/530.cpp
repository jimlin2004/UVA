#include <cstdio>

long long gcd(long long a, long long b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int main()
{
    long long n, k;
    while (scanf("%lld %lld", &n, &k))
    {
        if (n == 0 && k == 0)
            break;
        if (2 * k > n)
            k = n - k;
        if (k == 0)
        {
            printf("1\n");
            continue;
        }
        //邊乘邊除 x / y
        long long ans = 1;
        long long c;
        for (long long i = 1, j = n; i <= k; ++i, --j)
        {
            c = gcd(i, j);
            ans *= (j / c);
            ans /= (i / c);
        }
        printf("%lld\n", ans);
    }
    return 0;
}