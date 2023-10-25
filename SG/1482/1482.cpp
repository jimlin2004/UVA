#include <cstdio>
using namespace std;

//SG例題

//經觀察的結果
long long SG(long long x)
{
    if (x & 1)
        return SG(x / 2);
    else
        return x / 2;
}

int main()
{
    int t;
    scanf("%d", &t);
    int n;
    while (t--)
    {
        scanf("%d", &n);
        long long stones;
        long long res = 0;
        for (int i = 0; i < n; ++i)
        {
            scanf("%lld", &stones);
            res ^= SG(stones);
        }

        puts((res) ? "YES" : "NO");
    }
    return 0;
}