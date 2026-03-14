#include <cstdio>
using namespace std;

//SG例題

/*
    SG(x) = mex{ SG(y) | x -> y }

    首先SG(0) = 0 (沒有後繼狀態)
    SG(1) = 0 (因為只能拿最多一半)
    SG(2) = mex{ SG(1) } = mex{ 0 } = 1
    SG(3) = mex{ SG(2) } = mex{ 1 } = 0
    SG(4) = mex{ SG(2), SG(3) } = mex{ 0, 1 } = 2
    SG(5) = mex{ SG(3), SG(4) } = mex{ 0, 2 } = 1
    SG(6) = mex{ SG(3), SG(4), SG(5) } = mex{ 0, 2, 1 } = 3
    ...
    觀察到
    if x is even then
        return x / 2;
    if x is odd then
        return SG(x / 2)

*/

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