#include <iostream>
using namespace std;
#define maxn 100005

/*
    Greedy + 類似隊列優化

    維護一個答案隊列(陣列)res[]
    res裡的數字就是我選的答案
    當現在選的數字A[i]比之前選的還大且i -> n還夠組成答案需要的長度時
    代表我可以直接取代掉之前選的答案(ex: 因為18...一定比19...小)
    ex:
    N = 7, D = 4 -> 這裡改成我要選D = 7 - 4 = 3個數字
    A[] = {1, 2, 3, 4, 5, 6, 7}
    res[] = {}, cnt(即res的長度) = 0

    i = 0時選
    res[] = {1}, cnt = 1
    i = 1時發現A[i] = 2大於之前選的1且A[]中還有n - i - 1 = 5個數字可以選
    又D - cnt - 1 < 5
    所以2可以取代1
    res[] = {2}, cnt = 1
    一路下去依序為
    res[] = {3}, cnt = 1
    res[] = {4}, cnt = 1
    res[] = {5}, cnt = 1
    res[] = {5, 6}, cnt = 2
    res[] = {5, 6, 7}, cnt = 3
    結束
*/

char A[maxn];
char res[maxn];

int main()
{
    int n, d;
    while (scanf("%d %d", &n, &d) && (n != 0 && d != 0))
    {
        scanf("%s", &A);

        int cnt = 0;
        d = n - d;
        for (int i = 0; i < n; ++i)
        {
            while (cnt > 0 && (n - i > (d - cnt)) && res[cnt - 1] < A[i])
            {
                res[cnt--] = 0;
            }
            if (cnt < d)
                res[cnt++] = A[i];
        }

        res[cnt] = '\0'; //記得補\0
        printf("%s\n", res);
    }

    return 0;
}

/*
4 2
3759
4 3
9654
5 2
96124
5 2
96421
5 3
19212
4 2
9999
6 3
123123
7 2
1000000
7 3
1000000
7 4
1000000
20 8
12384569254752365478
10 3
1010101010
4 2
9573
10 3
9876543210
2 1
96
0 0
*/
