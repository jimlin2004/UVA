#include <cstdio>
#include <algorithm>
using namespace std;

/*
    與貪婪法1不同的在於只考慮
    1. 看最大與最小的能不能裝在同一個bin
    2. 都不行就只能放最大的在一個bin(自己一個)

    發現其實不用考慮最大與次大的放同個bin
    因為題目限定一個bin只能放兩個
    sort過後(由大到小)
    其實最大與次大的假設為ab
    由於sort，可知a <= b
    那其實我們只是把b去與一個目前最小的合成一個bin
    (一定有，因為sort過，a前面一定小於等於a)
    那a也一定有一個次小的(設為c)可以合成一個bin
    (因為原本可以與b和，既然sort過，c一定 < b)
    所以我們只是選擇不同的合成同個bin，不影響正確答案

    Note: 第一次打這題用的是這方法
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
            if (m - items[R] >= items[L])
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