#include <bits/stdc++.h>
using namespace std;

/*

這題的概念是每次交易都交給後面
也就是說當現在要買入就買
如果要賣出的就賣，不夠就跟後面的人預支
方法就是利用curr維護當前有多少item(可正可負)
其中的cost是abs(curr)，是負的會由後面的人負責補上
其cost就是搬過來的
此時用abs可以計算一樣的效果(因為abs是距離的概念)

*/

int main()
{
    int n;
    while (scanf("%d", &n) && n)
    {
        long long res = 0;
        long long curr = 0;
        long long A;
        for (int i = 0; i < n; ++i)
        {
            res += abs(curr);
            scanf("%lld", &A);
            curr += A;
        }

        printf("%lld\n", res);
    }

    return 0;
}