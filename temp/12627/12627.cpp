#include <cstdio>

long long pow2[31];
long long pow3[31];

long long f(long long k, long long i)
{
    if (i == 0)
        return 0;
    if (k == 0)
        return 1;
    long long half = pow2[k - 1];
    if (i <= half)
        return 2 * f(k - 1, i);
    return f(k - 1, i - half) + 2 * pow3[k - 1];
}

int main()
{
    pow2[0] = 1;
    pow3[0] = 1;
    for (int i = 1; i < 31; ++i)
    {
        pow2[i] = pow2[i - 1] * 2;
        pow3[i] = pow3[i - 1] * 3;
    }

    long long k, a, b;
    int t;
    scanf("%d", &t);
    for (int Case = 1; Case <= t; ++Case)
    {
        scanf("%lld %lld %lld", &k, &a, &b);
        printf("Case %d: %lld\n", Case, f(k, b) - f(k, a - 1));
    }
    return 0;
}