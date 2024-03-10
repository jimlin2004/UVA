#include <cstdio>
#include <algorithm>
using namespace std;

/*
經典Kadane
紀錄當前最小的與當前最大的
因為最小的(負值)乘上負數可能變最大值
最大的乘上負數可能變成最小值
*/

int main()
{
    int n;

    int Case = 0;
    while (scanf("%d", &n) != EOF)
    {
        long long num, currMinP, currMaxP;
        scanf("%lld", &num);
        long long res = num;
        currMinP = num;
        currMaxP = num;
        long long maxPTemp;
        for (int i = 1; i < n; ++i)
        {
            scanf("%lld", &num);
            maxPTemp = max(num, max(num * currMinP, num * currMaxP));
            currMinP = min(num, min(num * currMinP, num * currMaxP));
            currMaxP = maxPTemp;
            res = max(res, currMaxP);
        }

        printf("Case #%d: The maximum product is %lld.\n\n", ++Case, (res < 0) ? 0 : res);
    }
    return 0;
}