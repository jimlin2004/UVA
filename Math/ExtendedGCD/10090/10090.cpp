#include <iostream>
#include <cmath>
using namespace std;
#define ll long long

ll exgcd(ll a, ll b, ll& x, ll& y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    ll gcd = exgcd(b, a % b, x, y);
    ll y1 = y;
    y = x - (a / b) * y;
    x = y1;
    return gcd;
}

int main()
{
    ll n;
    ll x, y;
    ll c1, c2, n1, n2;
    while (~scanf("%lld", &n) && n)
    {
        scanf("%lld %lld", &c1, &n1);
        scanf("%lld %lld", &c2, &n2);
        ll gcd = exgcd(n1, n2, x, y);
        if (n % gcd != 0)
        {
            printf("failed\n");
            continue;
        }
        ll l = ceil((double)(-n) * x / n2);
        ll r = floor((double)(n) * y / n1);
        if (l > r)
        {
            printf("failed\n");
            continue;
        }
        if (c1 * n2 < c2 * n1) //斜率正or負
        {
            x = n * x / gcd + n2 / gcd * r;
            y = n * y / gcd - n1 / gcd * r;
        }
        else
        {
            x = n * x / gcd + n2 / gcd * l;
            y = n * y / gcd - n1 / gcd * l;
        }
        printf("%lld %lld\n", x, y);
    }
    return 0;
}