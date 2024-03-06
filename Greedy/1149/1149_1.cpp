#include <cstdio>
#include <algorithm>
using namespace std;

/*
貪婪法1:
    直覺的想，能塞就多塞點，所以sort後
    1. 看最大與次大的能不能裝在同一個bin
    2. 看最大與最小的能不能裝在同一個bin
    3. 都不行就只能放最大的在一個bin(自己一個)
貪婪法2在另一個檔案
*/

#define maxn 100005

int items[maxn];

int main()
{
    bool first = true;
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int n, m;
        scanf("%d", &n);
        scanf("%d", &m);
        for (int i = 0; i < n; ++i)
            scanf("%d", &items[i]);
        sort(items, items + n);

        int res = 0;
        int L = 0, R = n - 1;
        while (L <= R)
        {
            if (items[R] + items[R - 1] <= m)
            {
                ++res;
                R -= 2;
            }
            else if (m - items[R] >= items[L])
            {
                ++res;
                ++L;
                --R;
            }
            else
            {
                ++res;
                --R;
            }
        }

        if (first)
            first = false;
        else
            puts("");

        printf("%d\n", res);
    }
    return 0;
}