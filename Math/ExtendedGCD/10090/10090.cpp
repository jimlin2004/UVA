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
    ll c1, c2, a, b;
    while (~scanf("%lld", &n) && n)
    {
        scanf("%lld %lld", &c1, &a);
        scanf("%lld %lld", &c2, &b);
        ll gcd = exgcd(a, b, x, y);
        if (n % gcd != 0)
        {
            printf("failed\n");
            continue;
        }
        ll l = ceil((double)(-n) * x / b);
        ll r = floor((double)(n) * y / a);
        if (l > r)
        {
            printf("failed\n");
            continue;
        }
        if (c1 * b < c2 * a) //斜率正or負
        {
            //斜率負，帶入k的上界
            x = n * x / gcd + b / gcd * r;
            y = n * y / gcd - a / gcd * r;
        }
        else
        {
            //斜率正，帶入k的下界
            x = n * x / gcd + b / gcd * l;
            y = n * y / gcd - a / gcd * l;
        }
        printf("%lld %lld\n", x, y);
    }
    return 0;
}