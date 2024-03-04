#include <cstdio>
#include <cmath>
using namespace std;

//總之，解等差級數
//推導.png

long long solve(long long s)
{
    return floor( (-1 + sqrt(1 + 4 * (2 * s))) / 2.0 );
}

int main()
{
    int t;
    long long s;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%lld", &s);
        printf("%lld\n", solve(s));
    } 
    return 0;
}