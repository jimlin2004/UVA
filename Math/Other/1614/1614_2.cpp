#include <bits/stdc++.h>
using namespace std;

/*
    greedy 解法
    結論: 當給定n個數，滿足 1 <= a[i] <= i，則n個數可以組成1 ~ sum[n]的所有數字
    證明(數學歸納法):
        當n = 1時，a[1] = 1 = sum[1]滿足，
        設n = k時亦滿足，
        則當n = k + 1時
        由於sum[k + 1] = sum[k] + a[k + 1]
        已經假設a[1] ~ a[k]能組成1 ~ sum[k]，
        所以只需證明a[1] ~ a[k + 1]能組成sum[k] + 1 ~ sum[k + 1]的所有數
        
        設p滿足 1 <= p <= a[k + 1]
        因為sum[k] + p = sum[k] + a[k + 1] - (a[k + 1] - p) (多退少補)
        且1 <= a[k] <= k (題幹限制)
        所以sum[k] >= k且a[k + 1] - p <= k，
        已知前k個數可以組成1 ~ sum[k]，所以能夠湊出a[k + 1] - p
        所以從能夠湊出sum[k]的組合裡減去a[k + 1] - p，就能湊出sum[k] + p (回到多退少補的式子)
        結論: 前k + 1個數能夠湊出1 ~ sum[k + 1]的所有數

    因此只要sort後，是偶數的S下
    能夠扣掉S / 2的就扣，然後繼續搜
    最後一定有答案

*/

#define maxn 100005

pair<int, int> a[maxn];
int res[maxn];

int main()
{
    int n;
    while (scanf("%d", &n) != EOF)
    {
        long long S = 0;
        for (int i = 1; i <= n; ++i)
        {
            int val;
            scanf("%d", &val);
            S += val;
            a[i] = {val, i};
        }

        if (S % 2 != 0)
        {
            puts("No");
            continue;
        }

        sort(a + 1, a + 1 + n);

        S /= 2;
        for (int i = n; i >= 1; --i)
        {
            if (S >= a[i].first)
            {
                S -= a[i].first;
                res[a[i].second] = -1;
            }
            else
                res[a[i].second] = 1;
        }

        puts("Yes");
        printf("%d", res[1]);
        for (int i = 2; i <= n; ++i)
            printf(" %d", res[i]);
        puts("");
    }
    return 0;
}