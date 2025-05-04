#include <cstdio>
#include <algorithm>
using namespace std;

/*
prefix[i]為1到i在strA與strB中相同位置DNA不一樣的總個數

[l, r]中錯誤率為
(prefix[r] - prefix[l - 1]) / (r - l + 1) <= p / 100
移項 => 100 * (prefix[r] - prefix[l - 1]) <= (r - l + 1) * p
整理 => (l - 1) * p - 100 * prefix[l - 1] <= r * p - 100 * prefix[r]
移項 => 100 * prefix[l - 1] - p * (l - 1) >= 100 * prefix[r] - p * r

設f(i) = 100 * prefix[i] - p * i
上式即被簡化為f(l - 1) => f(r)

要求l ~ r越長越好
所以用二分法找到最長的距離
為了方便二分法
額外利用一個fm[]維護fm[i] = f -> 在i的左邊(包含)的最大f()
之後就是單純的二分了

*/

#define maxn 150005

char A[maxn];
char B[maxn];
int prefix[maxn];

int f[maxn];
int fm[maxn];
int n, p;

bool check(int len)
{
    for (int i = len; i <= n; ++i)
    {
        if (f[i] <= fm[i - len])
            return true;
    }
    return false;
}


int main()
{
    prefix[0] = 0;
    f[0] = 0;
    fm[0] = 0;

    while (scanf("%d %d", &n, &p) && n && p)
    {
        scanf("%s", A);
        scanf("%s", B);

        for (int i = 1; i <= n; ++i)
            prefix[i] = prefix[i - 1] + (A[i - 1] != B[i - 1]);
        
        for (int i = 1; i <= n; ++i)
            f[i] = 100 * prefix[i] - p * i;
        
        for (int i = 1; i <= n; ++i)
            fm[i] = max(fm[i - 1], f[i]);
        
        int L = 0, R = n + 1;
        while (L + 1 < R)
        {
            int mid = (L + R) / 2;
            if (check(mid))
                L = mid;
            else
                R = mid;
        }

        if (L == 0)
            puts("No solution.");
        else
            printf("%d\n", L);
    }

    return 0;
}