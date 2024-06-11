#include <cstdio>
#include <unordered_map>
using namespace std;

/*
    基本上很簡單
    就分兩邊
    A[i] + B[j]記錄在unordered_map<sum, count>中
    在枚舉-1 * (C[k] + D[z])有沒有在unorder_map中
    加起來即可
*/

#define maxn 4005

int A[maxn];
int B[maxn];
int C[maxn];
int D[maxn];

//<A + B, 出現幾次>
unordered_map<int, int> mp;

int main()
{
    bool first = true;

    int t;
    scanf("%d", &t);
    while (t--)
    {
        int n;
        scanf("%d", &n);

        mp.clear();

        for (int i = 0 ; i < n; ++i)
        {
            scanf("%d %d %d %d", &A[i], &B[i], &C[i], &D[i]);
        }

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                ++mp[A[i] + B[j]];
            }
        }

        int res = 0;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (mp.find(-1 * (C[i] + D[j])) != mp.end())
                    res += mp[-1 * (C[i] + D[j])];
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