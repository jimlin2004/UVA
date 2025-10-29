#include <bits/stdc++.h>
using namespace std;

// 冪次塔 -> 歐拉定理靶題

int n;
// ep[0]是冪次塔的底數
long long ep[15]; // 指數

long long phi(long long x)
{
    long long res = x;

    for (long long i = 2; i * i <= x; ++i)
    {
        if (x % i == 0)
        {
            res -= res / i;
            while (x % i == 0)
                x /= i;
        }
    }

    if (x > 1)
        res -= res / x;

    return res;
}

long long qpow(long long a, long long b, long long mod)
{
    long long res = 1;

    while (b > 0)
    {
        if (b & 1)
            res = res * a % mod;

        a = a * a % mod;
        b >>= 1;
    }

    return res % mod;
}

// 遞迴解冪次塔
// i是指第幾個冪次塔的數字
// 用歐拉定理  a^x = a^(x % phi(M) + phi(M)) mod M
/*
    ex:
        2^3^4^5 mod 10

        2^3^4^5 = 2^( 3^4^5 % phi(10) + phi(10) ) mod 10
        其中
        3^4^5 = 3^( 4^5 % phi(phi(10)) + phi(phi(10))) mod phi(10)
        ... 一路遞迴下去再算回來
*/
long long f(long long i, long long mod)
{
    if (i == n - 1) // 最後一層
    {
        return ep[i] % mod;
    }

    long long phi_of_mod = phi(mod);

    return qpow(ep[i], f(i + 1, phi_of_mod) + phi_of_mod, mod);
}

int main()
{
    char input[10];

    int testcase = 0;

    while (scanf("%s", &input) && (input[0] != '#'))
    {
        long long mod = atoll(input);

        scanf("%d", &n);

        for (int i = 0; i < n; ++i)
            scanf("%lld", &ep[i]);

        printf("Case #%d: %lld\n", ++testcase, f(0, mod));
    }

    return 0;
}