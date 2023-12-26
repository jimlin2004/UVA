#include <cstdio>
#include <algorithm>
using namespace std;

/*
概念:
    直接暴搜，但需要技巧
    <網路>
        當A[]中的子字串與B[]中的子字串是排列關係時
        若確定i為A[]的下左邊界，那麼在A[]中每往左加入一個元素j，
        B[]也對應有一個位置，才能滿足元素相同的要求
        由於是連續子字串且沒有重複數字，
        若在B中的最左邊為L，最右邊為R.
        當R - L + 1 == j - i + 1時
        答案要加一

    <我的注釋>
        換句話說
        A[i ~ j]的子字串長度為(j - i + 1)
        若A[i ~ j]映射到B[]時的index最小值L、最大值R
        (R - L + 1) == (j - i + 1)時
        代表A[i ~ j]在B[]中的分布也是連續的子字串且長度也是(j - i + 1) (只是可能是A[i ~ j]的子字串排列組合)
        我們就找到了一組答案

        index:      i , i + 1 , i + 2 , i + 3
        如A[] = {...1     2       4       3...}
        index:      j   j + 1   j + 2   j + 3
        而B[] = {...2     1       3       4...}

        如何快速映射A到B -> 用v[]
        在此v[]是一個映射array
        初始化v[B[i]] = i代表v紀錄著B[i]的index
        用v[A[i]]即可知道A[i]在B[]中對應元素的index在多少

        如此將A[]的1243(長度 (i + 3) - i + 1 = 4)
        映射到B[]的2134(最小的index L = j, 最大的index R = j + 3)
        長度亦為(j + 3) - j + 1 = 4
        所以我們找到了一組解

        以上A[]與B[]的i, j不失一般性，可知此方法在都是A[]或B[]的"連續"子字串與無重複的數字出現的條件下
        找到的一組解是合理的
*/

int a[3005];
int b[3005];
int v[3005];

int solve(int n)
{
    int res = 0;
    for (int i = 0; i < n; ++i)
    {
        int l = v[a[i]];
        int r = v[a[i]];
        for (int j = i + 1; j < n; ++j)
        {
            l = min(l, v[a[j]]);
            r = max(r, v[a[j]]);
            if (r - l + 1 == j - i + 1)
                ++res;
        }
    }
    return res;
}

int main()
{
    int n;
    while (scanf("%d", &n) && n)
    {
        for (int i = 0; i < n; ++i)
        {
            scanf("%d", &a[i]);
        }

        for (int i = 0; i < n; ++i)
        {
            scanf("%d", &b[i]);
            v[b[i]] = i;
        }

        printf("%d\n", solve(n));
    }
    return 0;
}