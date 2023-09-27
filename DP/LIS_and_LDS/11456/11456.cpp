#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int n;
int trains[2005];
int LIS[2005];
int LDS[2005];

/*
核心概念:將火車i作為中間點，利用逆序的LIS代表能放在i左邊最多有幾個，
逆序的LDS代表能放在i右邊的火車有多少個
*/

int main()
{
    int Case;
    scanf("%d", &Case);
    while (Case--)
    {
        scanf("%d", &n);
        for (int i = 0; i < n; ++i)
        {
            scanf("%d", &trains[i]);
        }

        int res = 0;
        //LIS and LDS(要從後面開始做)
        for (int i = n - 1; i >= 0; --i)
        {
            LIS[i] = 1;
            LDS[i] = 1;
            for (int j = n - 1; j >= i + 1; --j)
            {
                if (trains[j] < trains[i])
                {
                    LIS[i] = max(LIS[i], LIS[j] + 1);
                }
                if (trains[j] > trains[i])
                {
                    LDS[i] = max(LDS[i], LDS[j] + 1);
                }
            }

            res = max(res, LIS[i] + LDS[i] - 1); // -1 for 重複加到自己
        }
        printf("%d\n", res);
    }
    return 0;
}