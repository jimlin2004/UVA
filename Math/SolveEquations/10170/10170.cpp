#include <cstdio>
#include <cmath>

//基本上是等差級數解方程
//過程在推導.png

long long solve(long long a, long long d)
{
    return ceil( (-1 + sqrt(1 - 4 * (-(a * a) + a - 2 * d) )) / 2.0 );
}

int main()
{
    long long a, d;
    while (scanf("%lld %lld", &a, &d) != EOF)
    {
        printf("%lld\n", solve(a, d));
    }
    return 0;
}